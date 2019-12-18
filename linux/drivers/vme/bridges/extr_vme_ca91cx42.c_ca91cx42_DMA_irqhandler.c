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
typedef  int /*<<< orphan*/  u32 ;
struct ca91cx42_driver {int /*<<< orphan*/  dma_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA91CX42_LINT_DMA ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 ca91cx42_DMA_irqhandler(struct ca91cx42_driver *bridge)
{
	wake_up(&bridge->dma_queue);

	return CA91CX42_LINT_DMA;
}