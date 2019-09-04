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
typedef  int u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;

/* Variables and functions */
 int EHEA_BMASK_SET (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  H_REGBCMC_MACADDR ; 
 int /*<<< orphan*/  H_REGBCMC_PN ; 
 int /*<<< orphan*/  H_REGBCMC_REGTYPE ; 
 int /*<<< orphan*/  H_REGBCMC_VLANID ; 
 int ehea_plpar_hcall_norets (int /*<<< orphan*/  const,int const,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 ehea_h_reg_dereg_bcmc(const u64 adapter_handle, const u16 port_num,
			  const u8 reg_type, const u64 mc_mac_addr,
			  const u16 vlan_id, const u32 hcall_id)
{
	u64 r5_port_num, r6_reg_type, r7_mc_mac_addr, r8_vlan_id;
	u64 mac_addr = mc_mac_addr >> 16;

	r5_port_num = EHEA_BMASK_SET(H_REGBCMC_PN, port_num);
	r6_reg_type = EHEA_BMASK_SET(H_REGBCMC_REGTYPE, reg_type);
	r7_mc_mac_addr = EHEA_BMASK_SET(H_REGBCMC_MACADDR, mac_addr);
	r8_vlan_id = EHEA_BMASK_SET(H_REGBCMC_VLANID, vlan_id);

	return ehea_plpar_hcall_norets(hcall_id,
				       adapter_handle,		/* R4 */
				       r5_port_num,		/* R5 */
				       r6_reg_type,		/* R6 */
				       r7_mc_mac_addr,		/* R7 */
				       r8_vlan_id,		/* R8 */
				       0, 0);			/* R9-R12 */
}