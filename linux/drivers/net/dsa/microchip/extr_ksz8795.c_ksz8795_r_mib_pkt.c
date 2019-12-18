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
 int IND_ACC_TABLE (int) ; 
 int KS_MIB_TOTAL_RX_0 ; 
 int KS_MIB_TOTAL_RX_1 ; 
 int MIB_COUNTER_OVERFLOW ; 
 int MIB_COUNTER_VALID ; 
 int MIB_PACKET_DROPPED ; 
 int MIB_TOTAL_BYTES_H ; 
 int /*<<< orphan*/  REG_IND_CTRL_0 ; 
 int /*<<< orphan*/  REG_IND_DATA_LO ; 
 int /*<<< orphan*/  REG_IND_MIB_CHECK ; 
 scalar_t__ SWITCH_COUNTER_NUM ; 
 int TABLE_MIB ; 
 int TABLE_READ ; 
 int /*<<< orphan*/  ksz_read32 (struct ksz_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ksz_read8 (struct ksz_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ksz_write16 (struct ksz_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ksz8795_r_mib_pkt(struct ksz_device *dev, int port, u16 addr,
			      u64 *dropped, u64 *cnt)
{
	u16 ctrl_addr;
	u32 data;
	u8 check;
	int loop;

	addr -= SWITCH_COUNTER_NUM;
	ctrl_addr = (KS_MIB_TOTAL_RX_1 - KS_MIB_TOTAL_RX_0) * port;
	ctrl_addr += addr + KS_MIB_TOTAL_RX_0;
	ctrl_addr |= IND_ACC_TABLE(TABLE_MIB | TABLE_READ);

	mutex_lock(&dev->alu_mutex);
	ksz_write16(dev, REG_IND_CTRL_0, ctrl_addr);

	/* It is almost guaranteed to always read the valid bit because of
	 * slow SPI speed.
	 */
	for (loop = 2; loop > 0; loop--) {
		ksz_read8(dev, REG_IND_MIB_CHECK, &check);

		if (check & MIB_COUNTER_VALID) {
			ksz_read32(dev, REG_IND_DATA_LO, &data);
			if (addr < 2) {
				u64 total;

				total = check & MIB_TOTAL_BYTES_H;
				total <<= 32;
				*cnt += total;
				*cnt += data;
				if (check & MIB_COUNTER_OVERFLOW) {
					total = MIB_TOTAL_BYTES_H + 1;
					total <<= 32;
					*cnt += total;
				}
			} else {
				if (check & MIB_COUNTER_OVERFLOW)
					*cnt += MIB_PACKET_DROPPED + 1;
				*cnt += data & MIB_PACKET_DROPPED;
			}
			break;
		}
	}
	mutex_unlock(&dev->alu_mutex);
}