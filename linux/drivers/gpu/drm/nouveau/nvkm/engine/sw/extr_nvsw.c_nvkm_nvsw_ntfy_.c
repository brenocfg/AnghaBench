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
struct nvkm_object {int dummy; } ;
struct nvkm_nvsw {TYPE_1__* chan; } ;
struct nvkm_event {int dummy; } ;
struct TYPE_2__ {struct nvkm_event event; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NV04_NVSW_NTFY_UEVENT 128 
 struct nvkm_nvsw* nvkm_nvsw (struct nvkm_object*) ; 

__attribute__((used)) static int
nvkm_nvsw_ntfy_(struct nvkm_object *object, u32 mthd,
		struct nvkm_event **pevent)
{
	struct nvkm_nvsw *nvsw = nvkm_nvsw(object);
	switch (mthd) {
	case NV04_NVSW_NTFY_UEVENT:
		*pevent = &nvsw->chan->event;
		return 0;
	default:
		break;
	}
	return -EINVAL;
}