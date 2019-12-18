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
struct dispc_device {int is_enabled; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_CONFIG ; 
 scalar_t__ OMAP_DSS_LOAD_FRAME_ONLY ; 
 scalar_t__ REG_GET (struct dispc_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _omap_dispc_initial_config (struct dispc_device*) ; 
 struct dispc_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dispc_errata_i734_wa (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_restore_context (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_restore_gamma_tables (struct dispc_device*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int dispc_runtime_resume(struct device *dev)
{
	struct dispc_device *dispc = dev_get_drvdata(dev);

	/*
	 * The reset value for load mode is 0 (OMAP_DSS_LOAD_CLUT_AND_FRAME)
	 * but we always initialize it to 2 (OMAP_DSS_LOAD_FRAME_ONLY) in
	 * _omap_dispc_initial_config(). We can thus use it to detect if
	 * we have lost register context.
	 */
	if (REG_GET(dispc, DISPC_CONFIG, 2, 1) != OMAP_DSS_LOAD_FRAME_ONLY) {
		_omap_dispc_initial_config(dispc);

		dispc_errata_i734_wa(dispc);

		dispc_restore_context(dispc);

		dispc_restore_gamma_tables(dispc);
	}

	dispc->is_enabled = true;
	/* ensure the dispc_irq_handler sees the is_enabled value */
	smp_wmb();

	return 0;
}