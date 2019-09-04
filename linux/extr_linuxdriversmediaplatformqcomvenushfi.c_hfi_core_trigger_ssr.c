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
typedef  int /*<<< orphan*/  u32 ;
struct venus_core {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* core_trigger_ssr ) (struct venus_core*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct venus_core*,int /*<<< orphan*/ ) ; 

int hfi_core_trigger_ssr(struct venus_core *core, u32 type)
{
	return core->ops->core_trigger_ssr(core, type);
}