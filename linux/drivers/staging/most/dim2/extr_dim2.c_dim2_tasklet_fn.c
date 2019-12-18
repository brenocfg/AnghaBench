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
struct dim2_hdm {TYPE_1__* hch; } ;
struct TYPE_2__ {int /*<<< orphan*/  ch; int /*<<< orphan*/  is_initialized; } ;

/* Variables and functions */
 int DMA_CHANNELS ; 
 int /*<<< orphan*/  dim_lock ; 
 int /*<<< orphan*/  dim_service_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  service_done_flag (struct dim2_hdm*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  try_start_dim_transfer (TYPE_1__*) ; 

__attribute__((used)) static void dim2_tasklet_fn(unsigned long data)
{
	struct dim2_hdm *dev = (struct dim2_hdm *)data;
	unsigned long flags;
	int ch_idx;

	for (ch_idx = 0; ch_idx < DMA_CHANNELS; ch_idx++) {
		if (!dev->hch[ch_idx].is_initialized)
			continue;

		spin_lock_irqsave(&dim_lock, flags);
		dim_service_channel(&dev->hch[ch_idx].ch);
		spin_unlock_irqrestore(&dim_lock, flags);

		service_done_flag(dev, ch_idx);
		while (!try_start_dim_transfer(dev->hch + ch_idx))
			continue;
	}
}