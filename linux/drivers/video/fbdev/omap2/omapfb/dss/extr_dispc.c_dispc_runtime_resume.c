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
struct device {int dummy; } ;
struct TYPE_2__ {int is_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_CONFIG ; 
 scalar_t__ OMAP_DSS_LOAD_FRAME_ONLY ; 
 scalar_t__ REG_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _omap_dispc_initial_config () ; 
 TYPE_1__ dispc ; 
 int /*<<< orphan*/  dispc_restore_context () ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int dispc_runtime_resume(struct device *dev)
{
	/*
	 * The reset value for load mode is 0 (OMAP_DSS_LOAD_CLUT_AND_FRAME)
	 * but we always initialize it to 2 (OMAP_DSS_LOAD_FRAME_ONLY) in
	 * _omap_dispc_initial_config(). We can thus use it to detect if
	 * we have lost register context.
	 */
	if (REG_GET(DISPC_CONFIG, 2, 1) != OMAP_DSS_LOAD_FRAME_ONLY) {
		_omap_dispc_initial_config();

		dispc_restore_context();
	}

	dispc.is_enabled = true;
	/* ensure the dispc_irq_handler sees the is_enabled value */
	smp_wmb();

	return 0;
}