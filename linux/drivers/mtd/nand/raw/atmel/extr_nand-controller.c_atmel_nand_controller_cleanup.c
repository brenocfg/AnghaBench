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
struct atmel_nand_controller {int /*<<< orphan*/  mck; scalar_t__ dmac; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 

__attribute__((used)) static void atmel_nand_controller_cleanup(struct atmel_nand_controller *nc)
{
	if (nc->dmac)
		dma_release_channel(nc->dmac);

	clk_put(nc->mck);
}