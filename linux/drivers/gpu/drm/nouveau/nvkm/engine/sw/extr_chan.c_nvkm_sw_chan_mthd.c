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
struct nvkm_sw_chan {TYPE_1__* func; int /*<<< orphan*/  event; } ;
struct TYPE_2__ {int (* mthd ) (struct nvkm_sw_chan*,int,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_event_send (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct nvkm_sw_chan*,int,int,int) ; 

bool
nvkm_sw_chan_mthd(struct nvkm_sw_chan *chan, int subc, u32 mthd, u32 data)
{
	switch (mthd) {
	case 0x0000:
		return true;
	case 0x0500:
		nvkm_event_send(&chan->event, 1, 0, NULL, 0);
		return true;
	default:
		if (chan->func->mthd)
			return chan->func->mthd(chan, subc, mthd, data);
		break;
	}
	return false;
}