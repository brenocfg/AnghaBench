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
struct list_head {int dummy; } ;
struct dc_interrupt_params {int irq_source; int int_context; } ;
struct amdgpu_device {int dummy; } ;
typedef  int /*<<< orphan*/  int_params ;
typedef  enum dc_irq_source { ____Placeholder_dc_irq_source } dc_irq_source ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,void*,int) ; 
 int INTERRUPT_CONTEXT_NUMBER ; 
 int /*<<< orphan*/  memset (struct dc_interrupt_params*,int /*<<< orphan*/ ,int) ; 
 struct list_head* remove_irq_handler (struct amdgpu_device*,void*,struct dc_interrupt_params*) ; 
 int validate_irq_unregistration_params (int,void*) ; 

void amdgpu_dm_irq_unregister_interrupt(struct amdgpu_device *adev,
					enum dc_irq_source irq_source,
					void *ih)
{
	struct list_head *handler_list;
	struct dc_interrupt_params int_params;
	int i;

	if (false == validate_irq_unregistration_params(irq_source, ih))
		return;

	memset(&int_params, 0, sizeof(int_params));

	int_params.irq_source = irq_source;

	for (i = 0; i < INTERRUPT_CONTEXT_NUMBER; i++) {

		int_params.int_context = i;

		handler_list = remove_irq_handler(adev, ih, &int_params);

		if (handler_list != NULL)
			break;
	}

	if (handler_list == NULL) {
		/* If we got here, it means we searched all irq contexts
		 * for this irq source, but the handler was not found. */
		DRM_ERROR(
		"DM_IRQ: failed to find irq handler:%p for irq_source:%d!\n",
			ih, irq_source);
	}
}