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
struct mdc_dma {int /*<<< orphan*/  clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct mdc_dma* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int img_mdc_runtime_resume(struct device *dev)
{
	struct mdc_dma *mdma = dev_get_drvdata(dev);

	return clk_prepare_enable(mdma->clk);
}