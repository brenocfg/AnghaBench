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
struct adf_hw_device_data {int /*<<< orphan*/  fw_name; } ;
struct adf_fw_loader_data {int /*<<< orphan*/ * fw_loader; int /*<<< orphan*/ * mmp_fw; int /*<<< orphan*/ * uof_fw; } ;
struct adf_accel_dev {struct adf_hw_device_data* hw_device; struct adf_fw_loader_data* fw_loader; } ;

/* Variables and functions */
 int /*<<< orphan*/  qat_hal_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qat_uclo_del_uof_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

void adf_ae_fw_release(struct adf_accel_dev *accel_dev)
{
	struct adf_fw_loader_data *loader_data = accel_dev->fw_loader;
	struct adf_hw_device_data *hw_device = accel_dev->hw_device;

	if (!hw_device->fw_name)
		return;

	qat_uclo_del_uof_obj(loader_data->fw_loader);
	qat_hal_deinit(loader_data->fw_loader);
	release_firmware(loader_data->uof_fw);
	release_firmware(loader_data->mmp_fw);
	loader_data->uof_fw = NULL;
	loader_data->mmp_fw = NULL;
	loader_data->fw_loader = NULL;
}