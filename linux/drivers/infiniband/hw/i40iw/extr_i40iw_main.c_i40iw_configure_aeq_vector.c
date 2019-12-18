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
typedef  scalar_t__ u32 ;
struct i40iw_msix_vector {int /*<<< orphan*/  irq; } ;
struct i40iw_device {int /*<<< orphan*/  dpc_tasklet; int /*<<< orphan*/  msix_shared; struct i40iw_msix_vector* iw_msixtbl; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int I40IW_ERR_CONFIG ; 
 int /*<<< orphan*/  i40iw_dpc ; 
 int /*<<< orphan*/  i40iw_irq_handler ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct i40iw_device*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_configure_aeq_vector(struct i40iw_device *iwdev)
{
	struct i40iw_msix_vector *msix_vec = iwdev->iw_msixtbl;
	u32 ret = 0;

	if (!iwdev->msix_shared) {
		tasklet_init(&iwdev->dpc_tasklet, i40iw_dpc, (unsigned long)iwdev);
		ret = request_irq(msix_vec->irq, i40iw_irq_handler, 0, "i40iw", iwdev);
	}
	if (ret) {
		i40iw_pr_err("aeq irq config fail\n");
		return I40IW_ERR_CONFIG;
	}

	return 0;
}