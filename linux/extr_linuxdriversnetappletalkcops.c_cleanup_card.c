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
struct net_device {int /*<<< orphan*/  base_addr; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPS_IO_EXTENT ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct net_device*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_card(struct net_device *dev)
{
	if (dev->irq)
		free_irq(dev->irq, dev);
	release_region(dev->base_addr, COPS_IO_EXTENT);
}