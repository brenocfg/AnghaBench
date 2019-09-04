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
typedef  size_t u32 ;
struct ngene_channel {int /*<<< orphan*/  TSRingBuffer; int /*<<< orphan*/  RingBuffer; int /*<<< orphan*/  TSIdleBuffer; } ;
struct ngene {int /*<<< orphan*/  PAFWInterfaceBuffer; scalar_t__ FWInterfaceBuffer; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  PAOverflowBuffer; scalar_t__ OverflowBuffer; struct ngene_channel* channel; } ;

/* Variables and functions */
 size_t MAX_STREAM ; 
 int OVERFLOW_BUFFER_SIZE ; 
 size_t STREAM_VIDEOIN1 ; 
 int /*<<< orphan*/  free_idlebuffer (struct ngene*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_ringbuffer (struct ngene*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_common_buffers(struct ngene *dev)
{
	u32 i;
	struct ngene_channel *chan;

	for (i = STREAM_VIDEOIN1; i < MAX_STREAM; i++) {
		chan = &dev->channel[i];
		free_idlebuffer(dev, &chan->TSIdleBuffer, &chan->TSRingBuffer);
		free_ringbuffer(dev, &chan->RingBuffer);
		free_ringbuffer(dev, &chan->TSRingBuffer);
	}

	if (dev->OverflowBuffer)
		pci_free_consistent(dev->pci_dev,
				    OVERFLOW_BUFFER_SIZE,
				    dev->OverflowBuffer, dev->PAOverflowBuffer);

	if (dev->FWInterfaceBuffer)
		pci_free_consistent(dev->pci_dev,
				    4096,
				    dev->FWInterfaceBuffer,
				    dev->PAFWInterfaceBuffer);
}