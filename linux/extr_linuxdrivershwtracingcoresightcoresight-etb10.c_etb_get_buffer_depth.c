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
typedef  unsigned int u32 ;
struct etb_drvdata {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ETB_RAM_DEPTH_REG ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 unsigned int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static unsigned int etb_get_buffer_depth(struct etb_drvdata *drvdata)
{
	u32 depth = 0;

	pm_runtime_get_sync(drvdata->dev);

	/* RO registers don't need locking */
	depth = readl_relaxed(drvdata->base + ETB_RAM_DEPTH_REG);

	pm_runtime_put(drvdata->dev);
	return depth;
}