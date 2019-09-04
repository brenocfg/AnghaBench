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
typedef  int u32 ;
struct tx_sa {int dummy; } ;
struct rx_sa {int dummy; } ;
struct rx_ip_sa {int dummy; } ;
struct ixgbe_ipsec {struct ixgbe_ipsec* tx_tbl; struct ixgbe_ipsec* rx_tbl; struct ixgbe_ipsec* ip_tbl; scalar_t__ num_tx_sa; scalar_t__ num_rx_sa; int /*<<< orphan*/  rx_sa_list; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {TYPE_2__* netdev; struct ixgbe_ipsec* ipsec; struct ixgbe_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/ * xfrmdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IXGBE_IPSEC_MAX_RX_IP_COUNT ; 
 int IXGBE_IPSEC_MAX_SA_COUNT ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SECRXSTAT ; 
 int IXGBE_SECRXSTAT_SECRX_OFF_DIS ; 
 int /*<<< orphan*/  IXGBE_SECTXSTAT ; 
 int IXGBE_SECTXSTAT_SECTX_OFF_DIS ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_ipsec_clear_hw_tables (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_ipsec_stop_engine (struct ixgbe_adapter*) ; 
 scalar_t__ ixgbe_mac_82598EB ; 
 int /*<<< orphan*/  ixgbe_xfrmdev_ops ; 
 int /*<<< orphan*/  kfree (struct ixgbe_ipsec*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*) ; 

void ixgbe_init_ipsec_offload(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct ixgbe_ipsec *ipsec;
	u32 t_dis, r_dis;
	size_t size;

	if (hw->mac.type == ixgbe_mac_82598EB)
		return;

	/* If there is no support for either Tx or Rx offload
	 * we should not be advertising support for IPsec.
	 */
	t_dis = IXGBE_READ_REG(hw, IXGBE_SECTXSTAT) &
		IXGBE_SECTXSTAT_SECTX_OFF_DIS;
	r_dis = IXGBE_READ_REG(hw, IXGBE_SECRXSTAT) &
		IXGBE_SECRXSTAT_SECRX_OFF_DIS;
	if (t_dis || r_dis)
		return;

	ipsec = kzalloc(sizeof(*ipsec), GFP_KERNEL);
	if (!ipsec)
		goto err1;
	hash_init(ipsec->rx_sa_list);

	size = sizeof(struct rx_sa) * IXGBE_IPSEC_MAX_SA_COUNT;
	ipsec->rx_tbl = kzalloc(size, GFP_KERNEL);
	if (!ipsec->rx_tbl)
		goto err2;

	size = sizeof(struct tx_sa) * IXGBE_IPSEC_MAX_SA_COUNT;
	ipsec->tx_tbl = kzalloc(size, GFP_KERNEL);
	if (!ipsec->tx_tbl)
		goto err2;

	size = sizeof(struct rx_ip_sa) * IXGBE_IPSEC_MAX_RX_IP_COUNT;
	ipsec->ip_tbl = kzalloc(size, GFP_KERNEL);
	if (!ipsec->ip_tbl)
		goto err2;

	ipsec->num_rx_sa = 0;
	ipsec->num_tx_sa = 0;

	adapter->ipsec = ipsec;
	ixgbe_ipsec_stop_engine(adapter);
	ixgbe_ipsec_clear_hw_tables(adapter);

	adapter->netdev->xfrmdev_ops = &ixgbe_xfrmdev_ops;

	return;

err2:
	kfree(ipsec->ip_tbl);
	kfree(ipsec->rx_tbl);
	kfree(ipsec->tx_tbl);
	kfree(ipsec);
err1:
	netdev_err(adapter->netdev, "Unable to allocate memory for SA tables");
}