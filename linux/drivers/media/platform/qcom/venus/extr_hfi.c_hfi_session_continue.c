#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct venus_inst {struct venus_core* core; } ;
struct venus_core {TYPE_2__* ops; TYPE_1__* res; } ;
struct TYPE_4__ {int (* session_continue ) (struct venus_inst*) ;} ;
struct TYPE_3__ {scalar_t__ hfi_version; } ;

/* Variables and functions */
 scalar_t__ HFI_VERSION_1XX ; 
 int stub1 (struct venus_inst*) ; 

int hfi_session_continue(struct venus_inst *inst)
{
	struct venus_core *core = inst->core;

	if (core->res->hfi_version == HFI_VERSION_1XX)
		return 0;

	return core->ops->session_continue(inst);
}