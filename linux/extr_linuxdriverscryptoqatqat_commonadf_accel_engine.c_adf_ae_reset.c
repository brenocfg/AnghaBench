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
struct adf_fw_loader_data {int /*<<< orphan*/  fw_loader; } ;
struct adf_accel_dev {struct adf_fw_loader_data* fw_loader; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ qat_hal_clr_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qat_hal_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adf_ae_reset(struct adf_accel_dev *accel_dev, int ae)
{
	struct adf_fw_loader_data *loader_data = accel_dev->fw_loader;

	qat_hal_reset(loader_data->fw_loader);
	if (qat_hal_clr_reset(loader_data->fw_loader))
		return -EFAULT;

	return 0;
}