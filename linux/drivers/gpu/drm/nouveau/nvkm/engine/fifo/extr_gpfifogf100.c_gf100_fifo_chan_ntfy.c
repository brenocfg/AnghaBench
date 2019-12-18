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
typedef  int u32 ;
struct nvkm_fifo_chan {TYPE_1__* fifo; } ;
struct nvkm_event {int dummy; } ;
struct TYPE_2__ {struct nvkm_event kevent; struct nvkm_event uevent; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NV906F_V0_NTFY_KILLED 129 
#define  NV906F_V0_NTFY_NON_STALL_INTERRUPT 128 

int
gf100_fifo_chan_ntfy(struct nvkm_fifo_chan *chan, u32 type,
		     struct nvkm_event **pevent)
{
	switch (type) {
	case NV906F_V0_NTFY_NON_STALL_INTERRUPT:
		*pevent = &chan->fifo->uevent;
		return 0;
	case NV906F_V0_NTFY_KILLED:
		*pevent = &chan->fifo->kevent;
		return 0;
	default:
		break;
	}
	return -EINVAL;
}