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
struct ims_pcu {int /*<<< orphan*/  async_firmware_done; int /*<<< orphan*/  cmd_mutex; int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMS_PCU_FIRMWARE_NAME ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ihex_validate_fw (struct firmware const*) ; 
 int /*<<< orphan*/  ims_pcu_handle_firmware_update (struct ims_pcu*,struct firmware const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 

__attribute__((used)) static void ims_pcu_process_async_firmware(const struct firmware *fw,
					   void *context)
{
	struct ims_pcu *pcu = context;
	int error;

	if (!fw) {
		dev_err(pcu->dev, "Failed to get firmware %s\n",
			IMS_PCU_FIRMWARE_NAME);
		goto out;
	}

	error = ihex_validate_fw(fw);
	if (error) {
		dev_err(pcu->dev, "Firmware %s is invalid\n",
			IMS_PCU_FIRMWARE_NAME);
		goto out;
	}

	mutex_lock(&pcu->cmd_mutex);
	ims_pcu_handle_firmware_update(pcu, fw);
	mutex_unlock(&pcu->cmd_mutex);

	release_firmware(fw);

out:
	complete(&pcu->async_firmware_done);
}