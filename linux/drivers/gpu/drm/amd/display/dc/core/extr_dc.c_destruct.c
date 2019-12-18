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
struct dc {TYPE_1__* vm_helper; TYPE_1__* dcn_ip; TYPE_1__* dcn_soc; TYPE_1__* bw_dceip; TYPE_1__* bw_vbios; TYPE_1__* ctx; int /*<<< orphan*/ * clk_mgr; int /*<<< orphan*/ * current_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  perf_trace; int /*<<< orphan*/  dc_bios; scalar_t__ created_bios; scalar_t__ gpio_service; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_bios_parser_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dal_gpio_service_destroy (scalar_t__*) ; 
 int /*<<< orphan*/  dc_destroy_clk_mgr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dc_destroy_resource_pool (struct dc*) ; 
 int /*<<< orphan*/  dc_perf_trace_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dc_release_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_links (struct dc*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void destruct(struct dc *dc)
{
	if (dc->current_state) {
		dc_release_state(dc->current_state);
		dc->current_state = NULL;
	}

	destroy_links(dc);

	if (dc->clk_mgr) {
		dc_destroy_clk_mgr(dc->clk_mgr);
		dc->clk_mgr = NULL;
	}

	dc_destroy_resource_pool(dc);

	if (dc->ctx->gpio_service)
		dal_gpio_service_destroy(&dc->ctx->gpio_service);

	if (dc->ctx->created_bios)
		dal_bios_parser_destroy(&dc->ctx->dc_bios);

	dc_perf_trace_destroy(&dc->ctx->perf_trace);

	kfree(dc->ctx);
	dc->ctx = NULL;

	kfree(dc->bw_vbios);
	dc->bw_vbios = NULL;

	kfree(dc->bw_dceip);
	dc->bw_dceip = NULL;

#ifdef CONFIG_DRM_AMD_DC_DCN1_0
	kfree(dc->dcn_soc);
	dc->dcn_soc = NULL;

	kfree(dc->dcn_ip);
	dc->dcn_ip = NULL;

#endif
#ifdef CONFIG_DRM_AMD_DC_DCN2_0
	kfree(dc->vm_helper);
	dc->vm_helper = NULL;

#endif
}