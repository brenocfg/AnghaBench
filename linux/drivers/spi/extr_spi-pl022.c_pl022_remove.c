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
struct pl022 {int /*<<< orphan*/  pump_transfers; int /*<<< orphan*/  clk; TYPE_1__* master_info; } ;
struct amba_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ enable_dma; } ;

/* Variables and functions */
 struct pl022* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  amba_release_regions (struct amba_device*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_ssp_default_config (struct pl022*) ; 
 int /*<<< orphan*/  pl022_dma_remove (struct pl022*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pl022_remove(struct amba_device *adev)
{
	struct pl022 *pl022 = amba_get_drvdata(adev);

	if (!pl022)
		return 0;

	/*
	 * undo pm_runtime_put() in probe.  I assume that we're not
	 * accessing the primecell here.
	 */
	pm_runtime_get_noresume(&adev->dev);

	load_ssp_default_config(pl022);
	if (pl022->master_info->enable_dma)
		pl022_dma_remove(pl022);

	clk_disable_unprepare(pl022->clk);
	amba_release_regions(adev);
	tasklet_disable(&pl022->pump_transfers);
	return 0;
}