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
struct TYPE_2__ {scalar_t__ end_opd; scalar_t__ start_opd; } ;
struct module {TYPE_1__ arch; } ;

/* Variables and functions */
 void* dereference_function_descriptor (void*) ; 

void *dereference_module_function_descriptor(struct module *mod, void *ptr)
{
	if (ptr < (void *)mod->arch.start_opd ||
			ptr >= (void *)mod->arch.end_opd)
		return ptr;

	return dereference_function_descriptor(ptr);
}