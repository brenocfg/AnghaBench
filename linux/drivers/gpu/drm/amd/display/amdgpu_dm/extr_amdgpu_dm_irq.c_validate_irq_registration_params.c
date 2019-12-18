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
struct dc_interrupt_params {scalar_t__ int_context; scalar_t__ irq_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAL_VALID_IRQ_SRC_NUM (scalar_t__) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 scalar_t__ INTERRUPT_CONTEXT_NUMBER ; 

__attribute__((used)) static bool
validate_irq_registration_params(struct dc_interrupt_params *int_params,
				 void (*ih)(void *))
{
	if (NULL == int_params || NULL == ih) {
		DRM_ERROR("DM_IRQ: invalid input!\n");
		return false;
	}

	if (int_params->int_context >= INTERRUPT_CONTEXT_NUMBER) {
		DRM_ERROR("DM_IRQ: invalid context: %d!\n",
				int_params->int_context);
		return false;
	}

	if (!DAL_VALID_IRQ_SRC_NUM(int_params->irq_source)) {
		DRM_ERROR("DM_IRQ: invalid irq_source: %d!\n",
				int_params->irq_source);
		return false;
	}

	return true;
}