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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int chan_id; } ;
struct timb_dma_chan {TYPE_1__ chan; } ;
struct timb_dma {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct timb_dma *tdchantotd(struct timb_dma_chan *td_chan)
{
	int id = td_chan->chan.chan_id;
	return (struct timb_dma *)((u8 *)td_chan -
		id * sizeof(struct timb_dma_chan) - sizeof(struct timb_dma));
}