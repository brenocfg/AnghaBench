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
struct megasas_instance {int adapter_type; int /*<<< orphan*/ * reply_map; } ;

/* Variables and functions */
#define  AERO_SERIES 132 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  INVADER_SERIES 131 
#define  MFI_SERIES 130 
#define  THUNDERBOLT_SERIES 129 
#define  VENTURA_SERIES 128 
 int /*<<< orphan*/ * kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  megasas_alloc_fusion_context (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_alloc_mfi_ctrl_mem (struct megasas_instance*) ; 
 int /*<<< orphan*/  nr_cpu_ids ; 

__attribute__((used)) static int megasas_alloc_ctrl_mem(struct megasas_instance *instance)
{
	instance->reply_map = kcalloc(nr_cpu_ids, sizeof(unsigned int),
				      GFP_KERNEL);
	if (!instance->reply_map)
		return -ENOMEM;

	switch (instance->adapter_type) {
	case MFI_SERIES:
		if (megasas_alloc_mfi_ctrl_mem(instance))
			goto fail;
		break;
	case AERO_SERIES:
	case VENTURA_SERIES:
	case THUNDERBOLT_SERIES:
	case INVADER_SERIES:
		if (megasas_alloc_fusion_context(instance))
			goto fail;
		break;
	}

	return 0;
 fail:
	kfree(instance->reply_map);
	instance->reply_map = NULL;
	return -ENOMEM;
}