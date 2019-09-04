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
typedef  int u32 ;
struct flash_spec {int config1; int strapping; int config2; int config3; int write1; int total_size; } ;
struct bnx2 {int flash_size; struct flash_spec const* flash_info; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct flash_spec*) ; 
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int /*<<< orphan*/  BNX2_NVM_CFG1 ; 
 int /*<<< orphan*/  BNX2_NVM_CFG2 ; 
 int /*<<< orphan*/  BNX2_NVM_CFG3 ; 
 int /*<<< orphan*/  BNX2_NVM_WRITE1 ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int BNX2_SHARED_HW_CFG2_NVM_SIZE_MASK ; 
 int /*<<< orphan*/  BNX2_SHARED_HW_CFG_CONFIG2 ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 int ENODEV ; 
 int FLASH_BACKUP_STRAP_MASK ; 
 int FLASH_STRAP_MASK ; 
 int bnx2_acquire_nvram_lock (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_disable_nvram_access (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_enable_nvram_access (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_release_nvram_lock (struct bnx2*) ; 
 int bnx2_shmem_rd (struct bnx2*,int /*<<< orphan*/ ) ; 
 struct flash_spec const flash_5709 ; 
 struct flash_spec* flash_table ; 
 int /*<<< orphan*/  pr_alert (char*) ; 

__attribute__((used)) static int
bnx2_init_nvram(struct bnx2 *bp)
{
	u32 val;
	int j, entry_count, rc = 0;
	const struct flash_spec *flash;

	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		bp->flash_info = &flash_5709;
		goto get_flash_size;
	}

	/* Determine the selected interface. */
	val = BNX2_RD(bp, BNX2_NVM_CFG1);

	entry_count = ARRAY_SIZE(flash_table);

	if (val & 0x40000000) {

		/* Flash interface has been reconfigured */
		for (j = 0, flash = &flash_table[0]; j < entry_count;
		     j++, flash++) {
			if ((val & FLASH_BACKUP_STRAP_MASK) ==
			    (flash->config1 & FLASH_BACKUP_STRAP_MASK)) {
				bp->flash_info = flash;
				break;
			}
		}
	}
	else {
		u32 mask;
		/* Not yet been reconfigured */

		if (val & (1 << 23))
			mask = FLASH_BACKUP_STRAP_MASK;
		else
			mask = FLASH_STRAP_MASK;

		for (j = 0, flash = &flash_table[0]; j < entry_count;
			j++, flash++) {

			if ((val & mask) == (flash->strapping & mask)) {
				bp->flash_info = flash;

				/* Request access to the flash interface. */
				if ((rc = bnx2_acquire_nvram_lock(bp)) != 0)
					return rc;

				/* Enable access to flash interface */
				bnx2_enable_nvram_access(bp);

				/* Reconfigure the flash interface */
				BNX2_WR(bp, BNX2_NVM_CFG1, flash->config1);
				BNX2_WR(bp, BNX2_NVM_CFG2, flash->config2);
				BNX2_WR(bp, BNX2_NVM_CFG3, flash->config3);
				BNX2_WR(bp, BNX2_NVM_WRITE1, flash->write1);

				/* Disable access to flash interface */
				bnx2_disable_nvram_access(bp);
				bnx2_release_nvram_lock(bp);

				break;
			}
		}
	} /* if (val & 0x40000000) */

	if (j == entry_count) {
		bp->flash_info = NULL;
		pr_alert("Unknown flash/EEPROM type\n");
		return -ENODEV;
	}

get_flash_size:
	val = bnx2_shmem_rd(bp, BNX2_SHARED_HW_CFG_CONFIG2);
	val &= BNX2_SHARED_HW_CFG2_NVM_SIZE_MASK;
	if (val)
		bp->flash_size = val;
	else
		bp->flash_size = bp->flash_info->total_size;

	return rc;
}