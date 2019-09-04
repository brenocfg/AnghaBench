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
typedef  void* u64 ;
typedef  int u32 ;
struct qlcnic_adapter {int /*<<< orphan*/  ahw; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLCNIC_BOOTLOADER_ADDR ; 
 int /*<<< orphan*/  QLCNIC_BOOTLOADER_SIZE ; 
 void* QLCRDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int QLC_83XX_BOOTLOADER_FLASH_ADDR ; 
 int qlcnic_83xx_lockless_flash_read32 (struct qlcnic_adapter*,int,int /*<<< orphan*/ *,int) ; 
 int qlcnic_ms_mem_write128 (struct qlcnic_adapter*,void*,int*,int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int) ; 

__attribute__((used)) static int qlcnic_83xx_copy_bootloader(struct qlcnic_adapter *adapter)
{
	u8 *p_cache;
	u32 src, size;
	u64 dest;
	int ret = -EIO;

	src = QLC_83XX_BOOTLOADER_FLASH_ADDR;
	dest = QLCRDX(adapter->ahw, QLCNIC_BOOTLOADER_ADDR);
	size = QLCRDX(adapter->ahw, QLCNIC_BOOTLOADER_SIZE);

	/* alignment check */
	if (size & 0xF)
		size = (size + 16) & ~0xF;

	p_cache = vzalloc(size);
	if (p_cache == NULL)
		return -ENOMEM;

	ret = qlcnic_83xx_lockless_flash_read32(adapter, src, p_cache,
						size / sizeof(u32));
	if (ret) {
		vfree(p_cache);
		return ret;
	}
	/* 16 byte write to MS memory */
	ret = qlcnic_ms_mem_write128(adapter, dest, (u32 *)p_cache,
				     size / 16);
	if (ret) {
		vfree(p_cache);
		return ret;
	}
	vfree(p_cache);

	return ret;
}