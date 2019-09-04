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
typedef  scalar_t__ irq_handler_idx ;
typedef  enum dc_irq_source { ____Placeholder_dc_irq_source } dc_irq_source ;

/* Variables and functions */
 scalar_t__ DAL_INVALID_IRQ_HANDLER_IDX ; 
 int /*<<< orphan*/  DAL_VALID_IRQ_SRC_NUM (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 

__attribute__((used)) static bool validate_irq_unregistration_params(enum dc_irq_source irq_source,
					       irq_handler_idx handler_idx)
{
	if (DAL_INVALID_IRQ_HANDLER_IDX == handler_idx) {
		DRM_ERROR("DM_IRQ: invalid handler_idx==NULL!\n");
		return false;
	}

	if (!DAL_VALID_IRQ_SRC_NUM(irq_source)) {
		DRM_ERROR("DM_IRQ: invalid irq_source:%d!\n", irq_source);
		return false;
	}

	return true;
}