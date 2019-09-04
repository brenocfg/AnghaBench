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
typedef  int /*<<< orphan*/  u32 ;
struct nvif_ioctl_v0 {int type; unsigned long long token; void* owner; void* object; } ;
struct nouveau_abi16_chan {TYPE_1__* chan; } ;
struct TYPE_4__ {int /*<<< orphan*/  object; } ;
struct nouveau_abi16 {TYPE_2__ device; } ;
struct drm_file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSYS ; 
#define  NVIF_IOCTL_V0_MTHD 130 
#define  NVIF_IOCTL_V0_NEW 129 
 void* NVIF_IOCTL_V0_OWNER_ANY ; 
#define  NVIF_IOCTL_V0_SCLASS 128 
 struct nouveau_abi16* nouveau_abi16 (struct drm_file*) ; 
 struct nouveau_abi16_chan* nouveau_abi16_chan (struct nouveau_abi16*,unsigned long long) ; 
 void* nvif_handle (int /*<<< orphan*/ *) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_ioctl_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
nouveau_abi16_usif(struct drm_file *file_priv, void *data, u32 size)
{
	union {
		struct nvif_ioctl_v0 v0;
	} *args = data;
	struct nouveau_abi16_chan *chan;
	struct nouveau_abi16 *abi16;
	int ret = -ENOSYS;

	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, true))) {
		switch (args->v0.type) {
		case NVIF_IOCTL_V0_NEW:
		case NVIF_IOCTL_V0_MTHD:
		case NVIF_IOCTL_V0_SCLASS:
			break;
		default:
			return -EACCES;
		}
	} else
		return ret;

	if (!(abi16 = nouveau_abi16(file_priv)))
		return -ENOMEM;

	if (args->v0.token != ~0ULL) {
		if (!(chan = nouveau_abi16_chan(abi16, args->v0.token)))
			return -EINVAL;
		args->v0.object = nvif_handle(&chan->chan->user);
		args->v0.owner  = NVIF_IOCTL_V0_OWNER_ANY;
		return 0;
	}

	args->v0.object = nvif_handle(&abi16->device.object);
	args->v0.owner  = NVIF_IOCTL_V0_OWNER_ANY;
	return 0;
}