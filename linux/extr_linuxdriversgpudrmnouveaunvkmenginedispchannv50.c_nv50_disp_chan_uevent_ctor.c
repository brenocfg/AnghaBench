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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_notify {int size; int types; int /*<<< orphan*/  index; } ;
struct nvif_notify_uevent_req {int dummy; } ;
struct nvif_notify_uevent_rep {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  user; } ;
struct nv50_disp_chan {TYPE_1__ chid; } ;

/* Variables and functions */
 int ENOSYS ; 
 struct nv50_disp_chan* nv50_disp_chan (struct nvkm_object*) ; 
 int nvif_unvers (int,void**,int /*<<< orphan*/ *,struct nvif_notify_uevent_req) ; 

int
nv50_disp_chan_uevent_ctor(struct nvkm_object *object, void *data, u32 size,
			   struct nvkm_notify *notify)
{
	struct nv50_disp_chan *chan = nv50_disp_chan(object);
	union {
		struct nvif_notify_uevent_req none;
	} *args = data;
	int ret = -ENOSYS;

	if (!(ret = nvif_unvers(ret, &data, &size, args->none))) {
		notify->size  = sizeof(struct nvif_notify_uevent_rep);
		notify->types = 1;
		notify->index = chan->chid.user;
		return 0;
	}

	return ret;
}