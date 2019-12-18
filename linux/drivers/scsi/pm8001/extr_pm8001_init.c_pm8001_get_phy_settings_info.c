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
typedef  int /*<<< orphan*/  u8 ;
struct pm8001_ioctl_payload {int minor_function; int length; int /*<<< orphan*/  func_specific; scalar_t__ offset; } ;
struct pm8001_hba_info {int /*<<< orphan*/ * nvmd_completion; } ;
struct TYPE_2__ {int (* get_nvmd_req ) (struct pm8001_hba_info*,struct pm8001_ioctl_payload*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* PM8001_CHIP_DISP ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*) ; 
 int /*<<< orphan*/  pm8001_set_phy_profile (struct pm8001_hba_info*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct pm8001_hba_info*,struct pm8001_ioctl_payload*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pm8001_get_phy_settings_info(struct pm8001_hba_info *pm8001_ha)
{

#ifdef PM8001_READ_VPD
	/*OPTION ROM FLASH read for the SPC cards */
	DECLARE_COMPLETION_ONSTACK(completion);
	struct pm8001_ioctl_payload payload;
	int rc;

	pm8001_ha->nvmd_completion = &completion;
	/* SAS ADDRESS read from flash / EEPROM */
	payload.minor_function = 6;
	payload.offset = 0;
	payload.length = 4096;
	payload.func_specific = kzalloc(4096, GFP_KERNEL);
	if (!payload.func_specific)
		return -ENOMEM;
	/* Read phy setting values from flash */
	rc = PM8001_CHIP_DISP->get_nvmd_req(pm8001_ha, &payload);
	if (rc) {
		kfree(payload.func_specific);
		PM8001_INIT_DBG(pm8001_ha, pm8001_printk("nvmd failed\n"));
		return -ENOMEM;
	}
	wait_for_completion(&completion);
	pm8001_set_phy_profile(pm8001_ha, sizeof(u8), payload.func_specific);
	kfree(payload.func_specific);
#endif
	return 0;
}