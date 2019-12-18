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
struct TYPE_4__ {int lck_div; int pck_div; unsigned long lck; unsigned long pck; } ;
struct dsi_clk_calc_ctx {int /*<<< orphan*/  dsi_vm; TYPE_1__* config; int /*<<< orphan*/  vm; TYPE_2__ dispc_cinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/ * vm; } ;

/* Variables and functions */
 int dsi_vm_calc_blanking (struct dsi_clk_calc_ctx*) ; 
 int /*<<< orphan*/  print_dispc_vm (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_dsi_dispc_vm (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_dsi_vm (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool dsi_vm_calc_dispc_cb(int lckd, int pckd, unsigned long lck,
		unsigned long pck, void *data)
{
	struct dsi_clk_calc_ctx *ctx = data;

	ctx->dispc_cinfo.lck_div = lckd;
	ctx->dispc_cinfo.pck_div = pckd;
	ctx->dispc_cinfo.lck = lck;
	ctx->dispc_cinfo.pck = pck;

	if (dsi_vm_calc_blanking(ctx) == false)
		return false;

#ifdef PRINT_VERBOSE_VM_TIMINGS
	print_dispc_vm("dispc", &ctx->vm);
	print_dsi_vm("dsi  ", &ctx->dsi_vm);
	print_dispc_vm("req  ", ctx->config->vm);
	print_dsi_dispc_vm("act  ", &ctx->dsi_vm);
#endif

	return true;
}