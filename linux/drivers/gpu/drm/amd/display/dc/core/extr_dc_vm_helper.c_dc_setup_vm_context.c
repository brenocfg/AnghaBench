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
struct dc_virtual_addr_space_config {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init_vm_ctx ) (int /*<<< orphan*/ ,struct dc*,struct dc_virtual_addr_space_config*,int) ;} ;
struct dc {int /*<<< orphan*/  hwseq; TYPE_1__ hwss; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct dc*,struct dc_virtual_addr_space_config*,int) ; 

void dc_setup_vm_context(struct dc *dc, struct dc_virtual_addr_space_config *va_config, int vmid)
{
	dc->hwss.init_vm_ctx(dc->hwseq, dc, va_config, vmid);
}