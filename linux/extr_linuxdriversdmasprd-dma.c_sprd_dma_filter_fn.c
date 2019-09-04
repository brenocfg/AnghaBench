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
typedef  scalar_t__ u32 ;
struct sprd_dma_dev {scalar_t__ total_chns; } ;
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;
struct sprd_dma_chn {scalar_t__ chn_num; TYPE_1__ vc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct sprd_dma_chn* to_sprd_dma_chan (struct dma_chan*) ; 
 struct sprd_dma_dev* to_sprd_dma_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool sprd_dma_filter_fn(struct dma_chan *chan, void *param)
{
	struct sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	struct sprd_dma_dev *sdev = to_sprd_dma_dev(&schan->vc.chan);
	u32 req = *(u32 *)param;

	if (req < sdev->total_chns)
		return req == schan->chn_num + 1;
	else
		return false;
}