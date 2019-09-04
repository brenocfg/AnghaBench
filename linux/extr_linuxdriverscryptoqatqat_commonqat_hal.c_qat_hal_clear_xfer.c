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
struct icp_qat_fw_loader_handle {TYPE_1__* hal_handle; } ;
struct TYPE_2__ {unsigned char ae_max_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICP_DR_RD_ABS ; 
 unsigned short ICP_QAT_UCLO_MAX_GPR_REG ; 
 int /*<<< orphan*/  ICP_SR_RD_ABS ; 
 int /*<<< orphan*/  qat_hal_init_rd_xfer (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qat_hal_clear_xfer(struct icp_qat_fw_loader_handle *handle)
{
	unsigned char ae;
	unsigned short reg;

	for (ae = 0; ae < handle->hal_handle->ae_max_num; ae++) {
		for (reg = 0; reg < ICP_QAT_UCLO_MAX_GPR_REG; reg++) {
			qat_hal_init_rd_xfer(handle, ae, 0, ICP_SR_RD_ABS,
					     reg, 0);
			qat_hal_init_rd_xfer(handle, ae, 0, ICP_DR_RD_ABS,
					     reg, 0);
		}
	}
}