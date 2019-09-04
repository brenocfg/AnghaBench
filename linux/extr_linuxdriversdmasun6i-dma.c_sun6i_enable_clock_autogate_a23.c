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
struct sun6i_dma_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SUN8I_DMA_GATE ; 
 int /*<<< orphan*/  SUN8I_DMA_GATE_ENABLE ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sun6i_enable_clock_autogate_a23(struct sun6i_dma_dev *sdev)
{
	writel(SUN8I_DMA_GATE_ENABLE, sdev->base + SUN8I_DMA_GATE);
}