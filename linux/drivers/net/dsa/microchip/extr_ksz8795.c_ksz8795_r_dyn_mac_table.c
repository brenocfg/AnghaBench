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
typedef  int u32 ;
typedef  int u16 ;
struct ksz_device {int /*<<< orphan*/  alu_mutex; } ;

/* Variables and functions */
 int DYNAMIC_MAC_ENTRIES_H_S ; 
 int DYNAMIC_MAC_ENTRIES_S ; 
 int DYNAMIC_MAC_FID_S ; 
 int DYNAMIC_MAC_SRC_PORT_S ; 
 int DYNAMIC_MAC_TABLE_ENTRIES ; 
 int DYNAMIC_MAC_TABLE_ENTRIES_H ; 
 int DYNAMIC_MAC_TABLE_FID ; 
 int DYNAMIC_MAC_TABLE_SRC_PORT ; 
 int DYNAMIC_MAC_TABLE_TIMESTAMP ; 
 int DYNAMIC_MAC_TIMESTAMP_S ; 
 int EAGAIN ; 
 int ENXIO ; 
 int IND_ACC_TABLE (int) ; 
 int /*<<< orphan*/  REG_IND_CTRL_0 ; 
 int /*<<< orphan*/  REG_IND_DATA_HI ; 
 int TABLE_DYNAMIC_MAC ; 
 int TABLE_READ ; 
 int ksz8795_valid_dyn_entry (struct ksz_device*,int*) ; 
 int /*<<< orphan*/  ksz_read64 (struct ksz_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ksz_write16 (struct ksz_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ksz8795_r_dyn_mac_table(struct ksz_device *dev, u16 addr,
				   u8 *mac_addr, u8 *fid, u8 *src_port,
				   u8 *timestamp, u16 *entries)
{
	u32 data_hi, data_lo;
	u16 ctrl_addr;
	u8 data;
	int rc;

	ctrl_addr = IND_ACC_TABLE(TABLE_DYNAMIC_MAC | TABLE_READ) | addr;

	mutex_lock(&dev->alu_mutex);
	ksz_write16(dev, REG_IND_CTRL_0, ctrl_addr);

	rc = ksz8795_valid_dyn_entry(dev, &data);
	if (rc == -EAGAIN) {
		if (addr == 0)
			*entries = 0;
	} else if (rc == -ENXIO) {
		*entries = 0;
	/* At least one valid entry in the table. */
	} else {
		u64 buf = 0;
		int cnt;

		ksz_read64(dev, REG_IND_DATA_HI, &buf);
		data_hi = (u32)(buf >> 32);
		data_lo = (u32)buf;

		/* Check out how many valid entry in the table. */
		cnt = data & DYNAMIC_MAC_TABLE_ENTRIES_H;
		cnt <<= DYNAMIC_MAC_ENTRIES_H_S;
		cnt |= (data_hi & DYNAMIC_MAC_TABLE_ENTRIES) >>
			DYNAMIC_MAC_ENTRIES_S;
		*entries = cnt + 1;

		*fid = (data_hi & DYNAMIC_MAC_TABLE_FID) >>
			DYNAMIC_MAC_FID_S;
		*src_port = (data_hi & DYNAMIC_MAC_TABLE_SRC_PORT) >>
			DYNAMIC_MAC_SRC_PORT_S;
		*timestamp = (data_hi & DYNAMIC_MAC_TABLE_TIMESTAMP) >>
			DYNAMIC_MAC_TIMESTAMP_S;

		mac_addr[5] = (u8)data_lo;
		mac_addr[4] = (u8)(data_lo >> 8);
		mac_addr[3] = (u8)(data_lo >> 16);
		mac_addr[2] = (u8)(data_lo >> 24);

		mac_addr[1] = (u8)data_hi;
		mac_addr[0] = (u8)(data_hi >> 8);
		rc = 0;
	}
	mutex_unlock(&dev->alu_mutex);

	return rc;
}