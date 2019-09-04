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
struct mic_dma_chan {int /*<<< orphan*/  status_dest; int /*<<< orphan*/  status_dest_micpa; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  L1_CACHE_BYTES ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mbus_device (struct mic_dma_chan*) ; 

__attribute__((used)) static void mic_dma_free_status_dest(struct mic_dma_chan *ch)
{
	dma_unmap_single(&to_mbus_device(ch)->dev, ch->status_dest_micpa,
			 L1_CACHE_BYTES, DMA_BIDIRECTIONAL);
	kfree(ch->status_dest);
}