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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  param_dma ; 
 int /*<<< orphan*/  param_io ; 
 int /*<<< orphan*/  param_irq ; 
 int wbsd_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wbsd_probe(struct platform_device *dev)
{
	/* Use the module parameters for resources */
	return wbsd_init(&dev->dev, param_io, param_irq, param_dma, 0);
}