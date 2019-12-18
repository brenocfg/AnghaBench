#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {size_t nr_args; int /*<<< orphan*/ * args; scalar_t__ data_len; int /*<<< orphan*/  command; } ;
struct olpc_xo175_ec {int cmd_running; scalar_t__ cmd_state; size_t expected_resp_len; size_t resp_len; int /*<<< orphan*/  cmd_state_lock; int /*<<< orphan*/  gpio_cmd; int /*<<< orphan*/ * resp_data; TYPE_1__* spi; int /*<<< orphan*/  cmd_done; TYPE_2__ cmd; int /*<<< orphan*/  suspended; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ CMD_STATE_ERROR_RECEIVED ; 
 scalar_t__ CMD_STATE_WAITING_FOR_SWITCH ; 
 int EBUSY ; 
 int EOVERFLOW ; 
 int EREMOTEIO ; 
 int ETIMEDOUT ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t,...) ; 
 int /*<<< orphan*/  dev_err_ratelimited (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  olpc_xo175_ec_read_packet (struct olpc_xo175_ec*) ; 
 int olpc_xo175_ec_resp_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_slave_abort (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int olpc_xo175_ec_cmd(u8 cmd, u8 *inbuf, size_t inlen, u8 *resp,
					size_t resp_len, void *ec_cb_arg)
{
	struct olpc_xo175_ec *priv = ec_cb_arg;
	struct device *dev = &priv->spi->dev;
	unsigned long flags;
	size_t nr_bytes;
	int ret = 0;

	dev_dbg(dev, "CMD %x, %zd bytes expected\n", cmd, resp_len);

	if (inlen > 5) {
		dev_err(dev, "command len %zd too big!\n", resp_len);
		return -EOVERFLOW;
	}

	/* Suspending in the middle of an EC command hoses things badly! */
	if (WARN_ON(priv->suspended))
		return -EBUSY;

	/* Ensure a valid command and return bytes */
	ret = olpc_xo175_ec_resp_len(cmd);
	if (ret < 0) {
		dev_err_ratelimited(dev, "unknown command 0x%x\n", cmd);

		/*
		 * Assume the best in our callers, and allow unknown commands
		 * through. I'm not the charitable type, but it was beaten
		 * into me. Just maintain a minimum standard of sanity.
		 */
		if (resp_len > sizeof(priv->resp_data)) {
			dev_err(dev, "response too big: %zd!\n", resp_len);
			return -EOVERFLOW;
		}
		nr_bytes = resp_len;
	} else {
		nr_bytes = (size_t)ret;
		ret = 0;
	}
	resp_len = min(resp_len, nr_bytes);

	spin_lock_irqsave(&priv->cmd_state_lock, flags);

	/* Initialize the state machine */
	init_completion(&priv->cmd_done);
	priv->cmd_running = true;
	priv->cmd_state = CMD_STATE_WAITING_FOR_SWITCH;
	memset(&priv->cmd, 0, sizeof(priv->cmd));
	priv->cmd.command = cmd;
	priv->cmd.nr_args = inlen;
	priv->cmd.data_len = 0;
	memcpy(priv->cmd.args, inbuf, inlen);
	priv->expected_resp_len = nr_bytes;
	priv->resp_len = 0;

	/* Tickle the cmd gpio to get things started */
	gpiod_set_value_cansleep(priv->gpio_cmd, 1);

	spin_unlock_irqrestore(&priv->cmd_state_lock, flags);

	/* The irq handler should do the rest */
	if (!wait_for_completion_timeout(&priv->cmd_done,
			msecs_to_jiffies(4000))) {
		dev_err(dev, "EC cmd error: timeout in STATE %d\n",
				priv->cmd_state);
		gpiod_set_value_cansleep(priv->gpio_cmd, 0);
		spi_slave_abort(priv->spi);
		olpc_xo175_ec_read_packet(priv);
		return -ETIMEDOUT;
	}

	spin_lock_irqsave(&priv->cmd_state_lock, flags);

	/* Deal with the results. */
	if (priv->cmd_state == CMD_STATE_ERROR_RECEIVED) {
		/* EC-provided error is in the single response byte */
		dev_err(dev, "command 0x%x returned error 0x%x\n",
						cmd, priv->resp_data[0]);
		ret = -EREMOTEIO;
	} else if (priv->resp_len != nr_bytes) {
		dev_err(dev, "command 0x%x returned %d bytes, expected %zd bytes\n",
						cmd, priv->resp_len, nr_bytes);
		ret = -EREMOTEIO;
	} else {
		/*
		 * We may have 8 bytes in priv->resp, but we only care about
		 * what we've been asked for. If the caller asked for only 2
		 * bytes, give them that. We've guaranteed that
		 * resp_len <= priv->resp_len and priv->resp_len == nr_bytes.
		 */
		memcpy(resp, priv->resp_data, resp_len);
	}

	/* This should already be low, but just in case. */
	gpiod_set_value_cansleep(priv->gpio_cmd, 0);
	priv->cmd_running = false;

	spin_unlock_irqrestore(&priv->cmd_state_lock, flags);

	return ret;
}