#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dma_running; scalar_t__ dma_blk; } ;
struct saa7134_dev {TYPE_1__ dmasound; } ;

/* Variables and functions */
 int /*<<< orphan*/  saa7134_set_dmabits (struct saa7134_dev*) ; 

__attribute__((used)) static void saa7134_dma_start(struct saa7134_dev *dev)
{
	dev->dmasound.dma_blk     = 0;
	dev->dmasound.dma_running = 1;
	saa7134_set_dmabits(dev);
}