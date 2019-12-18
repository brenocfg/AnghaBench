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
struct ucsi_ccg {int /*<<< orphan*/  dev; } ;
typedef  enum enum_flash_mode { ____Placeholder_enum_flash_mode } enum_flash_mode ;

/* Variables and functions */
 int FLASH_NOT_NEEDED ; 
 int ccg_fw_update_needed (struct ucsi_ccg*,int*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int do_flash (struct ucsi_ccg*,int) ; 

__attribute__((used)) static int ccg_fw_update(struct ucsi_ccg *uc, enum enum_flash_mode flash_mode)
{
	int err = 0;

	while (flash_mode != FLASH_NOT_NEEDED) {
		err = do_flash(uc, flash_mode);
		if (err < 0)
			return err;
		err = ccg_fw_update_needed(uc, &flash_mode);
		if (err < 0)
			return err;
	}
	dev_info(uc->dev, "CCG FW update successful\n");

	return err;
}