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
struct device {int dummy; } ;
struct cio2_queue {int /*<<< orphan*/  fbpt_bus_addr; int /*<<< orphan*/  fbpt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO2_FBPT_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cio2_fbpt_exit(struct cio2_queue *q, struct device *dev)
{
	dma_free_coherent(dev, CIO2_FBPT_SIZE, q->fbpt, q->fbpt_bus_addr);
}