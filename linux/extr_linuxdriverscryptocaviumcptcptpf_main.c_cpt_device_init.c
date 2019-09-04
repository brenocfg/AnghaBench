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
typedef  scalar_t__ u64 ;
struct device {int dummy; } ;
struct cpt_device {int /*<<< orphan*/  flags; scalar_t__ next_group; scalar_t__ next_mc_idx; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPT_FLAG_DEVICE_READY ; 
 int ENODEV ; 
 scalar_t__ cpt_check_bist_status (struct cpt_device*) ; 
 scalar_t__ cpt_check_exe_bist_status (struct cpt_device*) ; 
 int /*<<< orphan*/  cpt_disable_all_cores (struct cpt_device*) ; 
 int /*<<< orphan*/  cpt_find_max_enabled_cores (struct cpt_device*) ; 
 int /*<<< orphan*/  cpt_reset (struct cpt_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int cpt_device_init(struct cpt_device *cpt)
{
	u64 bist;
	struct device *dev = &cpt->pdev->dev;

	/* Reset the PF when probed first */
	cpt_reset(cpt);
	msleep(100);

	/*Check BIST status*/
	bist = (u64)cpt_check_bist_status(cpt);
	if (bist) {
		dev_err(dev, "RAM BIST failed with code 0x%llx", bist);
		return -ENODEV;
	}

	bist = cpt_check_exe_bist_status(cpt);
	if (bist) {
		dev_err(dev, "Engine BIST failed with code 0x%llx", bist);
		return -ENODEV;
	}

	/*Get CLK frequency*/
	/*Get max enabled cores */
	cpt_find_max_enabled_cores(cpt);
	/*Disable all cores*/
	cpt_disable_all_cores(cpt);
	/*Reset device parameters*/
	cpt->next_mc_idx   = 0;
	cpt->next_group = 0;
	/* PF is ready */
	cpt->flags |= CPT_FLAG_DEVICE_READY;

	return 0;
}