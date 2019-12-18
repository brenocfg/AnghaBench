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
struct ufs_hba {int dev_quirks; } ;

/* Variables and functions */
 int UFS_DEVICE_QUIRK_HOST_PA_SAVECONFIGTIME ; 
 int ufs_qcom_quirk_host_pa_saveconfigtime (struct ufs_hba*) ; 

__attribute__((used)) static int ufs_qcom_apply_dev_quirks(struct ufs_hba *hba)
{
	int err = 0;

	if (hba->dev_quirks & UFS_DEVICE_QUIRK_HOST_PA_SAVECONFIGTIME)
		err = ufs_qcom_quirk_host_pa_saveconfigtime(hba);

	return err;
}