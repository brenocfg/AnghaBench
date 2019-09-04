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
typedef  scalar_t__ u32 ;
struct pch_can_priv {TYPE_1__* regs; } ;
struct net_device {int dummy; } ;
struct napi_struct {struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat; } ;

/* Variables and functions */
 scalar_t__ PCH_BUS_OFF ; 
 int /*<<< orphan*/  PCH_CAN_ALL ; 
 scalar_t__ PCH_LEC_ALL ; 
 scalar_t__ PCH_RX_OBJ_END ; 
 scalar_t__ PCH_RX_OBJ_START ; 
 scalar_t__ PCH_RX_OK ; 
 scalar_t__ PCH_STATUS_INT ; 
 scalar_t__ PCH_TX_OBJ_END ; 
 scalar_t__ PCH_TX_OBJ_START ; 
 scalar_t__ PCH_TX_OK ; 
 scalar_t__ ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_complete (struct napi_struct*) ; 
 struct pch_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pch_can_bit_clear (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pch_can_error (struct net_device*,scalar_t__) ; 
 scalar_t__ pch_can_int_pending (struct pch_can_priv*) ; 
 scalar_t__ pch_can_rx_normal (struct net_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  pch_can_set_int_enables (struct pch_can_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_can_tx_complete (struct net_device*,scalar_t__) ; 

__attribute__((used)) static int pch_can_poll(struct napi_struct *napi, int quota)
{
	struct net_device *ndev = napi->dev;
	struct pch_can_priv *priv = netdev_priv(ndev);
	u32 int_stat;
	u32 reg_stat;
	int quota_save = quota;

	int_stat = pch_can_int_pending(priv);
	if (!int_stat)
		goto end;

	if (int_stat == PCH_STATUS_INT) {
		reg_stat = ioread32(&priv->regs->stat);

		if ((reg_stat & (PCH_BUS_OFF | PCH_LEC_ALL)) &&
		   ((reg_stat & PCH_LEC_ALL) != PCH_LEC_ALL)) {
			pch_can_error(ndev, reg_stat);
			quota--;
		}

		if (reg_stat & (PCH_TX_OK | PCH_RX_OK))
			pch_can_bit_clear(&priv->regs->stat,
					  reg_stat & (PCH_TX_OK | PCH_RX_OK));

		int_stat = pch_can_int_pending(priv);
	}

	if (quota == 0)
		goto end;

	if ((int_stat >= PCH_RX_OBJ_START) && (int_stat <= PCH_RX_OBJ_END)) {
		quota -= pch_can_rx_normal(ndev, int_stat, quota);
	} else if ((int_stat >= PCH_TX_OBJ_START) &&
		   (int_stat <= PCH_TX_OBJ_END)) {
		/* Handle transmission interrupt */
		pch_can_tx_complete(ndev, int_stat);
	}

end:
	napi_complete(napi);
	pch_can_set_int_enables(priv, PCH_CAN_ALL);

	return quota_save - quota;
}