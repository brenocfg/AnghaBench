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
struct i40iw_device {int /*<<< orphan*/  init_state; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sd_type; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  HMC_OBJS_CREATED ; 
 int /*<<< orphan*/  I40IW_SD_TYPE_DIRECT ; 
 int /*<<< orphan*/  IW_CFG_FPM_QP_COUNT ; 
 int i40iw_config_fpm_values (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int i40iw_create_hmc_objs (struct i40iw_device*,int) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_hmc_setup(struct i40iw_device *iwdev)
{
	enum i40iw_status_code status;

	iwdev->sd_type = I40IW_SD_TYPE_DIRECT;
	status = i40iw_config_fpm_values(&iwdev->sc_dev, IW_CFG_FPM_QP_COUNT);
	if (status)
		goto exit;
	status = i40iw_create_hmc_objs(iwdev, true);
	if (status)
		goto exit;
	iwdev->init_state = HMC_OBJS_CREATED;
exit:
	return status;
}