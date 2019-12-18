#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct p54s_priv {scalar_t__ fw_state; int /*<<< orphan*/  mutex; TYPE_1__* spi; int /*<<< orphan*/  fw_comp; } ;
struct ieee80211_hw {struct p54s_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ FW_STATE_BOOTING ; 
 scalar_t__ FW_STATE_READY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p54spi_power_off (struct p54s_priv*) ; 
 int /*<<< orphan*/  p54spi_power_on (struct p54s_priv*) ; 
 int p54spi_upload_firmware (struct ieee80211_hw*) ; 
 unsigned long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int p54spi_op_start(struct ieee80211_hw *dev)
{
	struct p54s_priv *priv = dev->priv;
	unsigned long timeout;
	int ret = 0;

	if (mutex_lock_interruptible(&priv->mutex)) {
		ret = -EINTR;
		goto out;
	}

	priv->fw_state = FW_STATE_BOOTING;

	p54spi_power_on(priv);

	ret = p54spi_upload_firmware(dev);
	if (ret < 0) {
		p54spi_power_off(priv);
		goto out_unlock;
	}

	mutex_unlock(&priv->mutex);

	timeout = msecs_to_jiffies(2000);
	timeout = wait_for_completion_interruptible_timeout(&priv->fw_comp,
							    timeout);
	if (!timeout) {
		dev_err(&priv->spi->dev, "firmware boot failed");
		p54spi_power_off(priv);
		ret = -1;
		goto out;
	}

	if (mutex_lock_interruptible(&priv->mutex)) {
		ret = -EINTR;
		p54spi_power_off(priv);
		goto out;
	}

	WARN_ON(priv->fw_state != FW_STATE_READY);

out_unlock:
	mutex_unlock(&priv->mutex);

out:
	return ret;
}