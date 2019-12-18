#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct power_supply {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  command; } ;
struct TYPE_12__ {int channel; int byte; } ;
struct TYPE_13__ {TYPE_3__ resp; } ;
struct TYPE_11__ {int status; } ;
struct olpc_xo175_ec {int resp_len; int expected_resp_len; int* resp_data; int* logbuf; int /*<<< orphan*/  logbuf_len; TYPE_8__* pwrbtn; int /*<<< orphan*/  cmd_state_lock; int /*<<< orphan*/  cmd_done; void* cmd_state; scalar_t__ cmd_running; TYPE_6__ cmd; int /*<<< orphan*/  gpio_cmd; TYPE_4__ rx_buf; TYPE_2__ msg; TYPE_1__* spi; } ;
struct device {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  parent; } ;
struct TYPE_16__ {TYPE_5__ dev; } ;
struct TYPE_10__ {struct device dev; } ;

/* Variables and functions */
#define  CHAN_CMD_ERROR 143 
#define  CHAN_CMD_RESP 142 
#define  CHAN_DEBUG 141 
#define  CHAN_EVENT 140 
#define  CHAN_KEYBOARD 139 
#define  CHAN_NONE 138 
#define  CHAN_SWITCH 137 
#define  CHAN_TOUCHPAD 136 
 int /*<<< orphan*/  CMD_ECHO ; 
 void* CMD_STATE_CMD_IN_TX_FIFO ; 
 void* CMD_STATE_CMD_SENT ; 
 void* CMD_STATE_ERROR_RECEIVED ; 
 void* CMD_STATE_RESP_RECEIVED ; 
 int EINTR ; 
#define  EVENT_AC_CHANGE 135 
#define  EVENT_BATTERY_CRITICAL 134 
#define  EVENT_BATTERY_ERROR 133 
#define  EVENT_BATTERY_SOC_CHANGE 132 
#define  EVENT_BATTERY_STATUS 131 
#define  EVENT_POWER_PRESSED 130 
#define  EVENT_POWER_PRESS_WAKE 129 
#define  EVENT_TIMED_HOST_WAKE 128 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  LOG_BUF_SIZE ; 
 int /*<<< orphan*/  PM_WAKEUP_TIME ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (TYPE_8__*) ; 
 int /*<<< orphan*/  isprint (int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  olpc_xo175_ec_flush_logbuf (struct olpc_xo175_ec*) ; 
 int /*<<< orphan*/  olpc_xo175_ec_read_packet (struct olpc_xo175_ec*) ; 
 int /*<<< orphan*/  olpc_xo175_ec_send_command (struct olpc_xo175_ec*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_changed (struct power_supply*) ; 
 struct power_supply* power_supply_get_by_name (char*) ; 
 int /*<<< orphan*/  power_supply_put (struct power_supply*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void olpc_xo175_ec_complete(void *arg)
{
	struct olpc_xo175_ec *priv = arg;
	struct device *dev = &priv->spi->dev;
	struct power_supply *psy;
	unsigned long flags;
	u8 channel;
	u8 byte;
	int ret;

	ret = priv->msg.status;
	if (ret) {
		dev_err(dev, "SPI transfer failed: %d\n", ret);

		spin_lock_irqsave(&priv->cmd_state_lock, flags);
		if (priv->cmd_running) {
			priv->resp_len = 0;
			priv->cmd_state = CMD_STATE_ERROR_RECEIVED;
			complete(&priv->cmd_done);
		}
		spin_unlock_irqrestore(&priv->cmd_state_lock, flags);

		if (ret != -EINTR)
			olpc_xo175_ec_read_packet(priv);

		return;
	}

	channel = priv->rx_buf.resp.channel;
	byte = priv->rx_buf.resp.byte;

	switch (channel) {
	case CHAN_NONE:
		spin_lock_irqsave(&priv->cmd_state_lock, flags);

		if (!priv->cmd_running) {
			/* We can safely ignore these */
			dev_err(dev, "spurious FIFO read packet\n");
			spin_unlock_irqrestore(&priv->cmd_state_lock, flags);
			return;
		}

		priv->cmd_state = CMD_STATE_CMD_SENT;
		if (!priv->expected_resp_len)
			complete(&priv->cmd_done);
		olpc_xo175_ec_read_packet(priv);

		spin_unlock_irqrestore(&priv->cmd_state_lock, flags);
		return;

	case CHAN_SWITCH:
		spin_lock_irqsave(&priv->cmd_state_lock, flags);

		if (!priv->cmd_running) {
			/* Just go with the flow */
			dev_err(dev, "spurious SWITCH packet\n");
			memset(&priv->cmd, 0, sizeof(priv->cmd));
			priv->cmd.command = CMD_ECHO;
		}

		priv->cmd_state = CMD_STATE_CMD_IN_TX_FIFO;

		/* Throw command into TxFIFO */
		gpiod_set_value_cansleep(priv->gpio_cmd, 0);
		olpc_xo175_ec_send_command(priv, &priv->cmd, sizeof(priv->cmd));

		spin_unlock_irqrestore(&priv->cmd_state_lock, flags);
		return;

	case CHAN_CMD_RESP:
		spin_lock_irqsave(&priv->cmd_state_lock, flags);

		if (!priv->cmd_running) {
			dev_err(dev, "spurious response packet\n");
		} else if (priv->resp_len >= priv->expected_resp_len) {
			dev_err(dev, "too many response packets\n");
		} else {
			priv->resp_data[priv->resp_len++] = byte;
			if (priv->resp_len == priv->expected_resp_len) {
				priv->cmd_state = CMD_STATE_RESP_RECEIVED;
				complete(&priv->cmd_done);
			}
		}

		spin_unlock_irqrestore(&priv->cmd_state_lock, flags);
		break;

	case CHAN_CMD_ERROR:
		spin_lock_irqsave(&priv->cmd_state_lock, flags);

		if (!priv->cmd_running) {
			dev_err(dev, "spurious cmd error packet\n");
		} else {
			priv->resp_data[0] = byte;
			priv->resp_len = 1;
			priv->cmd_state = CMD_STATE_ERROR_RECEIVED;
			complete(&priv->cmd_done);
		}
		spin_unlock_irqrestore(&priv->cmd_state_lock, flags);
		break;

	case CHAN_KEYBOARD:
		dev_warn(dev, "keyboard is not supported\n");
		break;

	case CHAN_TOUCHPAD:
		dev_warn(dev, "touchpad is not supported\n");
		break;

	case CHAN_EVENT:
		dev_dbg(dev, "got event %.2x\n", byte);
		switch (byte) {
		case EVENT_AC_CHANGE:
			psy = power_supply_get_by_name("olpc-ac");
			if (psy) {
				power_supply_changed(psy);
				power_supply_put(psy);
			}
			break;
		case EVENT_BATTERY_STATUS:
		case EVENT_BATTERY_CRITICAL:
		case EVENT_BATTERY_SOC_CHANGE:
		case EVENT_BATTERY_ERROR:
			psy = power_supply_get_by_name("olpc-battery");
			if (psy) {
				power_supply_changed(psy);
				power_supply_put(psy);
			}
			break;
		case EVENT_POWER_PRESSED:
			input_report_key(priv->pwrbtn, KEY_POWER, 1);
			input_sync(priv->pwrbtn);
			input_report_key(priv->pwrbtn, KEY_POWER, 0);
			input_sync(priv->pwrbtn);
			/* fall through */
		case EVENT_POWER_PRESS_WAKE:
		case EVENT_TIMED_HOST_WAKE:
			pm_wakeup_event(priv->pwrbtn->dev.parent,
						PM_WAKEUP_TIME);
			break;
		default:
			dev_dbg(dev, "ignored unknown event %.2x\n", byte);
			break;
		}
		break;

	case CHAN_DEBUG:
		if (byte == '\n') {
			olpc_xo175_ec_flush_logbuf(priv);
		} else if (isprint(byte)) {
			priv->logbuf[priv->logbuf_len++] = byte;
			if (priv->logbuf_len == LOG_BUF_SIZE)
				olpc_xo175_ec_flush_logbuf(priv);
		}
		break;

	default:
		dev_warn(dev, "unknown channel: %d, %.2x\n", channel, byte);
		break;
	}

	/* Most non-command packets get the TxFIFO refilled and an ACK. */
	olpc_xo175_ec_read_packet(priv);
}