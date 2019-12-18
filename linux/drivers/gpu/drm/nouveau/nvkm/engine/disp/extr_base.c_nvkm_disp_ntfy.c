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
struct nvkm_object {int /*<<< orphan*/  engine; } ;
struct nvkm_event {int dummy; } ;
struct nvkm_disp {struct nvkm_event hpd; struct nvkm_event vblank; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NV04_DISP_NTFY_CONN 129 
#define  NV04_DISP_NTFY_VBLANK 128 
 struct nvkm_disp* nvkm_disp (int /*<<< orphan*/ ) ; 

int
nvkm_disp_ntfy(struct nvkm_object *object, u32 type, struct nvkm_event **event)
{
	struct nvkm_disp *disp = nvkm_disp(object->engine);
	switch (type) {
	case NV04_DISP_NTFY_VBLANK:
		*event = &disp->vblank;
		return 0;
	case NV04_DISP_NTFY_CONN:
		*event = &disp->hpd;
		return 0;
	default:
		break;
	}
	return -EINVAL;
}