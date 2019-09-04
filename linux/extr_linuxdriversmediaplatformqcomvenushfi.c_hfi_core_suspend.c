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
struct venus_core {scalar_t__ state; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* suspend ) (struct venus_core*) ;} ;

/* Variables and functions */
 scalar_t__ CORE_INIT ; 
 int stub1 (struct venus_core*) ; 

int hfi_core_suspend(struct venus_core *core)
{
	if (core->state != CORE_INIT)
		return 0;

	return core->ops->suspend(core);
}