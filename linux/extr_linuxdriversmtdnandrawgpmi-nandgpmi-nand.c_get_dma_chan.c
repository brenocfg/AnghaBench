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
struct gpmi_nand_data {struct dma_chan** dma_chans; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */

struct dma_chan *get_dma_chan(struct gpmi_nand_data *this)
{
	/* We use the DMA channel 0 to access all the nand chips. */
	return this->dma_chans[0];
}