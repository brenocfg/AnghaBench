#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sti_dvo {int enabled; int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_pix; TYPE_3__* panel; scalar_t__ regs; TYPE_2__* config; } ;
struct drm_bridge {struct sti_dvo* driver_private; } ;
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct TYPE_5__ {scalar_t__ awg_fwgen_fct; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 scalar_t__ DVO_AWG_DIGSYNC_CTRL ; 
 scalar_t__ DVO_DOF_CFG ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sti_dvo_disable(struct drm_bridge *bridge)
{
	struct sti_dvo *dvo = bridge->driver_private;

	if (!dvo->enabled)
		return;

	DRM_DEBUG_DRIVER("\n");

	if (dvo->config->awg_fwgen_fct)
		writel(0x00000000, dvo->regs + DVO_AWG_DIGSYNC_CTRL);

	writel(0x00000000, dvo->regs + DVO_DOF_CFG);

	if (dvo->panel)
		dvo->panel->funcs->disable(dvo->panel);

	/* Disable/unprepare dvo clock */
	clk_disable_unprepare(dvo->clk_pix);
	clk_disable_unprepare(dvo->clk);

	dvo->enabled = false;
}