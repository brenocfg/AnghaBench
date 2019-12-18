#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int QLCNIC_FLASH_SECTOR_SIZE ; 
 int QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  QLC_83XX_FLASH_DIRECT_DATA (int) ; 
 int /*<<< orphan*/  QLC_83XX_FLASH_DIRECT_WINDOW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_wrt_reg_indirect (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 

int qlcnic_83xx_lockless_flash_read32(struct qlcnic_adapter *adapter,
				      u32 flash_addr, u8 *p_data,
				      int count)
{
	u32 word, range, flash_offset, addr = flash_addr, ret;
	ulong indirect_add, direct_window;
	int i, err = 0;

	flash_offset = addr & (QLCNIC_FLASH_SECTOR_SIZE - 1);
	if (addr & 0x3) {
		dev_err(&adapter->pdev->dev, "Illegal addr = 0x%x\n", addr);
		return -EIO;
	}

	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_DIRECT_WINDOW,
				     (addr & 0xFFFF0000));

	range = flash_offset + (count * sizeof(u32));
	/* Check if data is spread across multiple sectors */
	if (range > (QLCNIC_FLASH_SECTOR_SIZE - 1)) {

		/* Multi sector read */
		for (i = 0; i < count; i++) {
			indirect_add = QLC_83XX_FLASH_DIRECT_DATA(addr);
			ret = QLCRD32(adapter, indirect_add, &err);
			if (err == -EIO)
				return err;

			word = ret;
			*(u32 *)p_data  = word;
			p_data = p_data + 4;
			addr = addr + 4;
			flash_offset = flash_offset + 4;

			if (flash_offset > (QLCNIC_FLASH_SECTOR_SIZE - 1)) {
				direct_window = QLC_83XX_FLASH_DIRECT_WINDOW;
				/* This write is needed once for each sector */
				qlcnic_83xx_wrt_reg_indirect(adapter,
							     direct_window,
							     (addr));
				flash_offset = 0;
			}
		}
	} else {
		/* Single sector read */
		for (i = 0; i < count; i++) {
			indirect_add = QLC_83XX_FLASH_DIRECT_DATA(addr);
			ret = QLCRD32(adapter, indirect_add, &err);
			if (err == -EIO)
				return err;

			word = ret;
			*(u32 *)p_data  = word;
			p_data = p_data + 4;
			addr = addr + 4;
		}
	}

	return 0;
}