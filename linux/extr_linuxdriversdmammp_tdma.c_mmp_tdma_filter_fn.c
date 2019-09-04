#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmp_tdma_filter_param {scalar_t__ of_node; scalar_t__ chan_id; } ;
struct TYPE_3__ {struct dma_device* device; } ;
struct mmp_tdma_chan {TYPE_1__ chan; } ;
struct dma_device {TYPE_2__* dev; } ;
struct dma_chan {scalar_t__ chan_id; } ;
struct TYPE_4__ {scalar_t__ of_node; } ;

/* Variables and functions */
 struct mmp_tdma_chan* to_mmp_tdma_chan (struct dma_chan*) ; 

__attribute__((used)) static bool mmp_tdma_filter_fn(struct dma_chan *chan, void *fn_param)
{
	struct mmp_tdma_filter_param *param = fn_param;
	struct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);
	struct dma_device *pdma_device = tdmac->chan.device;

	if (pdma_device->dev->of_node != param->of_node)
		return false;

	if (chan->chan_id != param->chan_id)
		return false;

	return true;
}