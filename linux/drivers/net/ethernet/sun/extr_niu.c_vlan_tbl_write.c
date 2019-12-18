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
typedef  int u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_VLAN_TBL (unsigned long) ; 
 int ENET_VLAN_TBL_SHIFT (int) ; 
 int ENET_VLAN_TBL_VLANRDCTBLN ; 
 int ENET_VLAN_TBL_VPR ; 
 int nr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 
 int vlan_entry_set_parity (int) ; 

__attribute__((used)) static void vlan_tbl_write(struct niu *np, unsigned long index,
			   int port, int vpr, int rdc_table)
{
	u64 reg_val = nr64(ENET_VLAN_TBL(index));

	reg_val &= ~((ENET_VLAN_TBL_VPR |
		      ENET_VLAN_TBL_VLANRDCTBLN) <<
		     ENET_VLAN_TBL_SHIFT(port));
	if (vpr)
		reg_val |= (ENET_VLAN_TBL_VPR <<
			    ENET_VLAN_TBL_SHIFT(port));
	reg_val |= (rdc_table << ENET_VLAN_TBL_SHIFT(port));

	reg_val = vlan_entry_set_parity(reg_val);

	nw64(ENET_VLAN_TBL(index), reg_val);
}