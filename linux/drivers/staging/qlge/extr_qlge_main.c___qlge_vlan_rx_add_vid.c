#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ql_adapter {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_ADDR_E ; 
 int /*<<< orphan*/  MAC_ADDR_TYPE_VLAN ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_set_mac_addr_reg (struct ql_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __qlge_vlan_rx_add_vid(struct ql_adapter *qdev, u16 vid)
{
	u32 enable_bit = MAC_ADDR_E;
	int err;

	err = ql_set_mac_addr_reg(qdev, (u8 *) &enable_bit,
				  MAC_ADDR_TYPE_VLAN, vid);
	if (err)
		netif_err(qdev, ifup, qdev->ndev,
			  "Failed to init vlan address.\n");
	return err;
}