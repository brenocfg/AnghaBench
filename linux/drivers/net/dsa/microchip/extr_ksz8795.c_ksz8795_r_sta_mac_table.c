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
typedef  void* u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ksz_device {int dummy; } ;
struct alu_struct {int port_forward; int is_override; int is_use_fid; int fid; void** mac; } ;

/* Variables and functions */
 int ENXIO ; 
 int STATIC_MAC_FID_S ; 
 int STATIC_MAC_FWD_PORTS_S ; 
 int STATIC_MAC_TABLE_FID ; 
 int STATIC_MAC_TABLE_FWD_PORTS ; 
 int STATIC_MAC_TABLE_OVERRIDE ; 
 int STATIC_MAC_TABLE_USE_FID ; 
 int STATIC_MAC_TABLE_VALID ; 
 int /*<<< orphan*/  TABLE_STATIC_MAC ; 
 int /*<<< orphan*/  ksz8795_r_table (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ksz8795_r_sta_mac_table(struct ksz_device *dev, u16 addr,
				   struct alu_struct *alu)
{
	u32 data_hi, data_lo;
	u64 data;

	ksz8795_r_table(dev, TABLE_STATIC_MAC, addr, &data);
	data_hi = data >> 32;
	data_lo = (u32)data;
	if (data_hi & (STATIC_MAC_TABLE_VALID | STATIC_MAC_TABLE_OVERRIDE)) {
		alu->mac[5] = (u8)data_lo;
		alu->mac[4] = (u8)(data_lo >> 8);
		alu->mac[3] = (u8)(data_lo >> 16);
		alu->mac[2] = (u8)(data_lo >> 24);
		alu->mac[1] = (u8)data_hi;
		alu->mac[0] = (u8)(data_hi >> 8);
		alu->port_forward = (data_hi & STATIC_MAC_TABLE_FWD_PORTS) >>
			STATIC_MAC_FWD_PORTS_S;
		alu->is_override =
			(data_hi & STATIC_MAC_TABLE_OVERRIDE) ? 1 : 0;
		data_hi >>= 1;
		alu->is_use_fid = (data_hi & STATIC_MAC_TABLE_USE_FID) ? 1 : 0;
		alu->fid = (data_hi & STATIC_MAC_TABLE_FID) >>
			STATIC_MAC_FID_S;
		return 0;
	}
	return -ENXIO;
}