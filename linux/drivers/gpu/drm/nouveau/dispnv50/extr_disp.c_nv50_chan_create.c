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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvif_sclass {scalar_t__ const oclass; } ;
struct nvif_object {int dummy; } ;
struct nvif_device {int dummy; } ;
struct nv50_chan {int /*<<< orphan*/  user; struct nvif_device* device; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ENOSYS ; 
 int nvif_object_init (struct nvif_object*,int /*<<< orphan*/ ,scalar_t__ const,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvif_object_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nvif_object_sclass_get (struct nvif_object*,struct nvif_sclass**) ; 
 int /*<<< orphan*/  nvif_object_sclass_put (struct nvif_sclass**) ; 

__attribute__((used)) static int
nv50_chan_create(struct nvif_device *device, struct nvif_object *disp,
		 const s32 *oclass, u8 head, void *data, u32 size,
		 struct nv50_chan *chan)
{
	struct nvif_sclass *sclass;
	int ret, i, n;

	chan->device = device;

	ret = n = nvif_object_sclass_get(disp, &sclass);
	if (ret < 0)
		return ret;

	while (oclass[0]) {
		for (i = 0; i < n; i++) {
			if (sclass[i].oclass == oclass[0]) {
				ret = nvif_object_init(disp, 0, oclass[0],
						       data, size, &chan->user);
				if (ret == 0)
					nvif_object_map(&chan->user, NULL, 0);
				nvif_object_sclass_put(&sclass);
				return ret;
			}
		}
		oclass++;
	}

	nvif_object_sclass_put(&sclass);
	return -ENOSYS;
}