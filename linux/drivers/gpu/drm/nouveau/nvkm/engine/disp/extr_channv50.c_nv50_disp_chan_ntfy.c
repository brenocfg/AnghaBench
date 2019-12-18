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
typedef  int u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_event {int dummy; } ;
struct nv50_disp_chan {struct nv50_disp* disp; } ;
struct nv50_disp {struct nvkm_event uevent; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NV50_DISP_CORE_CHANNEL_DMA_V0_NTFY_UEVENT 128 
 struct nv50_disp_chan* nv50_disp_chan (struct nvkm_object*) ; 

__attribute__((used)) static int
nv50_disp_chan_ntfy(struct nvkm_object *object, u32 type,
		    struct nvkm_event **pevent)
{
	struct nv50_disp_chan *chan = nv50_disp_chan(object);
	struct nv50_disp *disp = chan->disp;
	switch (type) {
	case NV50_DISP_CORE_CHANNEL_DMA_V0_NTFY_UEVENT:
		*pevent = &disp->uevent;
		return 0;
	default:
		break;
	}
	return -EINVAL;
}