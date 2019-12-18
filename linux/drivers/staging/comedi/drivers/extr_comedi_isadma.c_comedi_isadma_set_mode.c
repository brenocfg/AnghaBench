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
struct comedi_isadma_desc {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 char COMEDI_ISADMA_READ ; 
 int /*<<< orphan*/  DMA_MODE_READ ; 
 int /*<<< orphan*/  DMA_MODE_WRITE ; 

void comedi_isadma_set_mode(struct comedi_isadma_desc *desc, char dma_dir)
{
	desc->mode = (dma_dir == COMEDI_ISADMA_READ) ? DMA_MODE_READ
						     : DMA_MODE_WRITE;
}