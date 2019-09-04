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
struct TYPE_4__ {scalar_t__ position; void* channel; void* phys; } ;
struct TYPE_3__ {scalar_t__ position; void* channel; void* phys; } ;
struct tegra_ivc {void (* notify ) (struct tegra_ivc*,void*) ;size_t frame_size; unsigned int num_frames; TYPE_2__ rx; TYPE_1__ tx; void* notify_data; struct device* peer; } ;
struct device {int dummy; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int E2BIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t INT_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 void* dma_map_single (struct device*,void*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,void*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,void*,size_t,int /*<<< orphan*/ ) ; 
 int tegra_ivc_check_params (unsigned long,unsigned long,unsigned int,size_t) ; 
 size_t tegra_ivc_total_queue_size (unsigned int) ; 

int tegra_ivc_init(struct tegra_ivc *ivc, struct device *peer, void *rx,
		   dma_addr_t rx_phys, void *tx, dma_addr_t tx_phys,
		   unsigned int num_frames, size_t frame_size,
		   void (*notify)(struct tegra_ivc *ivc, void *data),
		   void *data)
{
	size_t queue_size;
	int err;

	if (WARN_ON(!ivc || !notify))
		return -EINVAL;

	/*
	 * All sizes that can be returned by communication functions should
	 * fit in an int.
	 */
	if (frame_size > INT_MAX)
		return -E2BIG;

	err = tegra_ivc_check_params((unsigned long)rx, (unsigned long)tx,
				     num_frames, frame_size);
	if (err < 0)
		return err;

	queue_size = tegra_ivc_total_queue_size(num_frames * frame_size);

	if (peer) {
		ivc->rx.phys = dma_map_single(peer, rx, queue_size,
					      DMA_BIDIRECTIONAL);
		if (dma_mapping_error(peer, ivc->rx.phys))
			return -ENOMEM;

		ivc->tx.phys = dma_map_single(peer, tx, queue_size,
					      DMA_BIDIRECTIONAL);
		if (dma_mapping_error(peer, ivc->tx.phys)) {
			dma_unmap_single(peer, ivc->rx.phys, queue_size,
					 DMA_BIDIRECTIONAL);
			return -ENOMEM;
		}
	} else {
		ivc->rx.phys = rx_phys;
		ivc->tx.phys = tx_phys;
	}

	ivc->rx.channel = rx;
	ivc->tx.channel = tx;
	ivc->peer = peer;
	ivc->notify = notify;
	ivc->notify_data = data;
	ivc->frame_size = frame_size;
	ivc->num_frames = num_frames;

	/*
	 * These values aren't necessarily correct until the channel has been
	 * reset.
	 */
	ivc->tx.position = 0;
	ivc->rx.position = 0;

	return 0;
}