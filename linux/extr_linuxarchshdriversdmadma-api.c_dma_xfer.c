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
struct dma_info {TYPE_1__* ops; } ;
struct dma_channel {unsigned long sar; unsigned long dar; size_t count; unsigned int mode; } ;
struct TYPE_2__ {int (* xfer ) (struct dma_channel*) ;} ;

/* Variables and functions */
 struct dma_channel* get_dma_channel (unsigned int) ; 
 struct dma_info* get_dma_info (unsigned int) ; 
 int stub1 (struct dma_channel*) ; 

int dma_xfer(unsigned int chan, unsigned long from,
	     unsigned long to, size_t size, unsigned int mode)
{
	struct dma_info *info = get_dma_info(chan);
	struct dma_channel *channel = get_dma_channel(chan);

	channel->sar	= from;
	channel->dar	= to;
	channel->count	= size;
	channel->mode	= mode;

	return info->ops->xfer(channel);
}