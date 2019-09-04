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
struct tegra_dma_channel {struct tegra_dma* tdma; } ;
struct tegra_dma {scalar_t__ global_pause_count; int /*<<< orphan*/  global_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_APBDMA_GENERAL ; 
 int /*<<< orphan*/  TEGRA_APBDMA_GENERAL_ENABLE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdma_write (struct tegra_dma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_dma_global_resume(struct tegra_dma_channel *tdc)
{
	struct tegra_dma *tdma = tdc->tdma;

	spin_lock(&tdma->global_lock);

	if (WARN_ON(tdc->tdma->global_pause_count == 0))
		goto out;

	if (--tdc->tdma->global_pause_count == 0)
		tdma_write(tdma, TEGRA_APBDMA_GENERAL,
			   TEGRA_APBDMA_GENERAL_ENABLE);

out:
	spin_unlock(&tdma->global_lock);
}