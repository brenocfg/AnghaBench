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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ieee802154_hw {struct adf7242_local* priv; } ;
struct adf7242_local {scalar_t__ tx_stat; int /*<<< orphan*/  flags; TYPE_1__* spi; int /*<<< orphan*/  tx_complete; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RC_CSMACA ; 
 int /*<<< orphan*/  CMD_RC_PHY_RDY ; 
 int ECOMM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FLAG_XMIT ; 
 int HZ ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  adf7242_clear_irqstat (struct adf7242_local*) ; 
 int adf7242_cmd (struct adf7242_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adf7242_cmd_rx (struct adf7242_local*) ; 
 int adf7242_write_fbuf (struct adf7242_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int adf7242_xmit(struct ieee802154_hw *hw, struct sk_buff *skb)
{
	struct adf7242_local *lp = hw->priv;
	int ret;

	/* ensure existing instances of the IRQ handler have completed */
	disable_irq(lp->spi->irq);
	set_bit(FLAG_XMIT, &lp->flags);
	cancel_delayed_work_sync(&lp->work);
	reinit_completion(&lp->tx_complete);
	adf7242_cmd(lp, CMD_RC_PHY_RDY);
	adf7242_clear_irqstat(lp);

	ret = adf7242_write_fbuf(lp, skb->data, skb->len);
	if (ret)
		goto err;

	ret = adf7242_cmd(lp, CMD_RC_CSMACA);
	if (ret)
		goto err;
	enable_irq(lp->spi->irq);

	ret = wait_for_completion_interruptible_timeout(&lp->tx_complete,
							HZ / 10);
	if (ret < 0)
		goto err;
	if (ret == 0) {
		dev_dbg(&lp->spi->dev, "Timeout waiting for TX interrupt\n");
		ret = -ETIMEDOUT;
		goto err;
	}

	if (lp->tx_stat != SUCCESS) {
		dev_dbg(&lp->spi->dev,
			"Error xmit: Retry count exceeded Status=0x%x\n",
			lp->tx_stat);
		ret = -ECOMM;
	} else {
		ret = 0;
	}

err:
	clear_bit(FLAG_XMIT, &lp->flags);
	adf7242_cmd_rx(lp);

	return ret;
}