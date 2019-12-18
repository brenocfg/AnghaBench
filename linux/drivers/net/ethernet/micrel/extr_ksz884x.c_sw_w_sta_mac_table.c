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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ksz_hw {int dummy; } ;

/* Variables and functions */
 int STATIC_MAC_FID_SHIFT ; 
 int STATIC_MAC_FWD_PORTS_SHIFT ; 
 int STATIC_MAC_TABLE_OVERRIDE ; 
 int STATIC_MAC_TABLE_USE_FID ; 
 int STATIC_MAC_TABLE_VALID ; 
 int /*<<< orphan*/  TABLE_STATIC_MAC ; 
 int /*<<< orphan*/  sw_w_table_64 (struct ksz_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void sw_w_sta_mac_table(struct ksz_hw *hw, u16 addr, u8 *mac_addr,
	u8 ports, int override, int valid, int use_fid, u8 fid)
{
	u32 data_hi;
	u32 data_lo;

	data_lo = ((u32) mac_addr[2] << 24) |
		((u32) mac_addr[3] << 16) |
		((u32) mac_addr[4] << 8) | mac_addr[5];
	data_hi = ((u32) mac_addr[0] << 8) | mac_addr[1];
	data_hi |= (u32) ports << STATIC_MAC_FWD_PORTS_SHIFT;

	if (override)
		data_hi |= STATIC_MAC_TABLE_OVERRIDE;
	if (use_fid) {
		data_hi |= STATIC_MAC_TABLE_USE_FID;
		data_hi |= (u32) fid << STATIC_MAC_FID_SHIFT;
	}
	if (valid)
		data_hi |= STATIC_MAC_TABLE_VALID;

	sw_w_table_64(hw, TABLE_STATIC_MAC, addr, data_hi, data_lo);
}