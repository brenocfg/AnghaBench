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
typedef  int u8 ;
struct sdio_func {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  wakeup_wait; } ;
struct ks_wlan_private {scalar_t__ dev_state; int /*<<< orphan*/  rw_dwork; int /*<<< orphan*/  wq; TYPE_1__ psstatus; int /*<<< orphan*/  net_dev; scalar_t__ wakeup_count; } ;
struct ks_sdio_card {struct ks_wlan_private* priv; } ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_BOOT ; 
 int GCR_B_ACTIVE ; 
 int /*<<< orphan*/  GCR_B_REG ; 
 int INT_GCR_B ; 
 int /*<<< orphan*/  INT_PENDING_REG ; 
 scalar_t__ PS_SNOOZE ; 
 int /*<<< orphan*/  PS_WAKEUP ; 
 int RSIZE_MASK ; 
 int WSTATUS_MASK ; 
 int /*<<< orphan*/  WSTATUS_RSIZE_REG ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int ks7010_sdio_readb (struct ks_wlan_private*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ks_wlan_hw_rx (struct ks_wlan_private*,size_t) ; 
 int /*<<< orphan*/  ks_wlan_hw_wakeup_request (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct ks_sdio_card* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  tx_device_task (struct ks_wlan_private*) ; 
 scalar_t__ txq_has_space (struct ks_wlan_private*) ; 

__attribute__((used)) static void ks_sdio_interrupt(struct sdio_func *func)
{
	int ret;
	struct ks_sdio_card *card;
	struct ks_wlan_private *priv;
	u8 status, rsize, byte;

	card = sdio_get_drvdata(func);
	priv = card->priv;

	if (priv->dev_state < DEVICE_STATE_BOOT)
		goto queue_delayed_work;

	ret = ks7010_sdio_readb(priv, INT_PENDING_REG, &status);
	if (ret) {
		netdev_err(priv->net_dev, "read INT_PENDING_REG\n");
		goto queue_delayed_work;
	}

	/* schedule task for interrupt status */
	/* bit7 -> Write General Communication B register */
	/* read (General Communication B register) */
	/* bit5 -> Write Status Idle */
	/* bit2 -> Read Status Busy  */
	if (status & INT_GCR_B ||
	    atomic_read(&priv->psstatus.status) == PS_SNOOZE) {
		ret = ks7010_sdio_readb(priv, GCR_B_REG, &byte);
		if (ret) {
			netdev_err(priv->net_dev, "read GCR_B_REG\n");
			goto queue_delayed_work;
		}
		if (byte == GCR_B_ACTIVE) {
			if (atomic_read(&priv->psstatus.status) == PS_SNOOZE) {
				atomic_set(&priv->psstatus.status, PS_WAKEUP);
				priv->wakeup_count = 0;
			}
			complete(&priv->psstatus.wakeup_wait);
		}
	}

	do {
		/* read (WriteStatus/ReadDataSize FN1:00_0014) */
		ret = ks7010_sdio_readb(priv, WSTATUS_RSIZE_REG, &byte);
		if (ret) {
			netdev_err(priv->net_dev, "read WSTATUS_RSIZE_REG\n");
			goto queue_delayed_work;
		}
		rsize = byte & RSIZE_MASK;
		if (rsize != 0)		/* Read schedule */
			ks_wlan_hw_rx(priv, (size_t)(rsize << 4));

		if (byte & WSTATUS_MASK) {
			if (atomic_read(&priv->psstatus.status) == PS_SNOOZE) {
				if (txq_has_space(priv)) {
					ks_wlan_hw_wakeup_request(priv);
					queue_delayed_work(priv->wq,
							   &priv->rw_dwork, 1);
					return;
				}
			} else {
				tx_device_task(priv);
			}
		}
	} while (rsize);

queue_delayed_work:
	queue_delayed_work(priv->wq, &priv->rw_dwork, 0);
}