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
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int of_dma_configure (struct device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int host1x_dma_configure(struct device *dev)
{
	return of_dma_configure(dev, dev->of_node, true);
}