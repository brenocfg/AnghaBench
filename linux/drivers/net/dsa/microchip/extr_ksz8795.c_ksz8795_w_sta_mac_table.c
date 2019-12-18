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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ksz_device {int dummy; } ;
struct alu_struct {int* mac; scalar_t__ is_static; scalar_t__ fid; scalar_t__ is_use_fid; scalar_t__ is_override; scalar_t__ port_forward; } ;

/* Variables and functions */
 int STATIC_MAC_FID_S ; 
 int STATIC_MAC_FWD_PORTS_S ; 
 int STATIC_MAC_TABLE_OVERRIDE ; 
 int STATIC_MAC_TABLE_USE_FID ; 
 int STATIC_MAC_TABLE_VALID ; 
 int /*<<< orphan*/  TABLE_STATIC_MAC ; 
 int /*<<< orphan*/  ksz8795_w_table (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ksz8795_w_sta_mac_table(struct ksz_device *dev, u16 addr,
				    struct alu_struct *alu)
{
	u32 data_hi, data_lo;
	u64 data;

	data_lo = ((u32)alu->mac[2] << 24) |
		((u32)alu->mac[3] << 16) |
		((u32)alu->mac[4] << 8) | alu->mac[5];
	data_hi = ((u32)alu->mac[0] << 8) | alu->mac[1];
	data_hi |= (u32)alu->port_forward << STATIC_MAC_FWD_PORTS_S;

	if (alu->is_override)
		data_hi |= STATIC_MAC_TABLE_OVERRIDE;
	if (alu->is_use_fid) {
		data_hi |= STATIC_MAC_TABLE_USE_FID;
		data_hi |= (u32)alu->fid << STATIC_MAC_FID_S;
	}
	if (alu->is_static)
		data_hi |= STATIC_MAC_TABLE_VALID;
	else
		data_hi &= ~STATIC_MAC_TABLE_OVERRIDE;

	data = (u64)data_hi << 32 | data_lo;
	ksz8795_w_table(dev, TABLE_STATIC_MAC, addr, data);
}