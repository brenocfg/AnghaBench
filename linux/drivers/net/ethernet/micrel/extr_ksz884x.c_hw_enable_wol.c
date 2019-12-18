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
typedef  int u32 ;
struct ksz_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS8841_WOL_FRAME0_ENABLE ; 
 int /*<<< orphan*/  KS8841_WOL_FRAME1_ENABLE ; 
 int /*<<< orphan*/  KS8841_WOL_FRAME2_ENABLE ; 
 int /*<<< orphan*/  KS8841_WOL_FRAME3_ENABLE ; 
 int /*<<< orphan*/  KS8841_WOL_MAGIC_ENABLE ; 
 int WAKE_ARP ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MCAST ; 
 int WAKE_UCAST ; 
 int /*<<< orphan*/  hw_add_wol_arp (struct ksz_hw*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hw_add_wol_mcast (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_add_wol_ucast (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_cfg_wol (struct ksz_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hw_enable_wol(struct ksz_hw *hw, u32 wol_enable, const u8 *net_addr)
{
	hw_cfg_wol(hw, KS8841_WOL_MAGIC_ENABLE, (wol_enable & WAKE_MAGIC));
	hw_cfg_wol(hw, KS8841_WOL_FRAME0_ENABLE, (wol_enable & WAKE_UCAST));
	hw_add_wol_ucast(hw);
	hw_cfg_wol(hw, KS8841_WOL_FRAME1_ENABLE, (wol_enable & WAKE_MCAST));
	hw_add_wol_mcast(hw);
	hw_cfg_wol(hw, KS8841_WOL_FRAME2_ENABLE, (wol_enable & WAKE_BCAST));
	hw_cfg_wol(hw, KS8841_WOL_FRAME3_ENABLE, (wol_enable & WAKE_ARP));
	hw_add_wol_arp(hw, net_addr);
}