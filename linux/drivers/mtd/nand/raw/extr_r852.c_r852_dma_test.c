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
struct r852_device {int dma_usable; } ;

/* Variables and functions */
 int R852_DMA1 ; 
 int R852_DMA2 ; 
 int /*<<< orphan*/  R852_DMA_CAP ; 
 int /*<<< orphan*/  message (char*) ; 
 int /*<<< orphan*/  r852_enable_dma ; 
 int r852_read_reg (struct r852_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r852_dma_test(struct r852_device *dev)
{
	dev->dma_usable = (r852_read_reg(dev, R852_DMA_CAP) &
		(R852_DMA1 | R852_DMA2)) == (R852_DMA1 | R852_DMA2);

	if (!dev->dma_usable)
		message("Non dma capable device detected, dma disabled");

	if (!r852_enable_dma) {
		message("disabling dma on user request");
		dev->dma_usable = 0;
	}
}