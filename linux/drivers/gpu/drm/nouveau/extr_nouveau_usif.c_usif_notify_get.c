#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct usif_notify {TYPE_4__* p; int /*<<< orphan*/  enabled; scalar_t__ reply; } ;
struct nvif_ioctl_ntfy_del_v0 {int /*<<< orphan*/  index; } ;
struct nvif_client {int dummy; } ;
struct nouveau_cli {struct nvif_client base; } ;
struct drm_file {int dummy; } ;
struct TYPE_7__ {scalar_t__ length; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {TYPE_2__ base; } ;
struct TYPE_6__ {struct drm_file* file_priv; TYPE_2__* event; } ;
struct TYPE_9__ {TYPE_3__ e; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_NOUVEAU_EVENT_NVIF ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_xchg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 TYPE_4__* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct nouveau_cli* nouveau_cli (struct drm_file*) ; 
 int nvif_client_ioctl (struct nvif_client*,void*,int /*<<< orphan*/ ) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_ioctl_ntfy_del_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct usif_notify* usif_notify_find (struct drm_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
usif_notify_get(struct drm_file *f, void *data, u32 size, void *argv, u32 argc)
{
	struct nouveau_cli *cli = nouveau_cli(f);
	struct nvif_client *client = &cli->base;
	union {
		struct nvif_ioctl_ntfy_del_v0 v0;
	} *args = data;
	struct usif_notify *ntfy;
	int ret = -ENOSYS;

	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, true))) {
		if (!(ntfy = usif_notify_find(f, args->v0.index)))
			return -ENOENT;
	} else
		return ret;

	if (atomic_xchg(&ntfy->enabled, 1))
		return 0;

	ntfy->p = kmalloc(sizeof(*ntfy->p) + ntfy->reply, GFP_KERNEL);
	if (ret = -ENOMEM, !ntfy->p)
		goto done;
	ntfy->p->base.event = &ntfy->p->e.base;
	ntfy->p->base.file_priv = f;
	ntfy->p->e.base.type = DRM_NOUVEAU_EVENT_NVIF;
	ntfy->p->e.base.length = sizeof(ntfy->p->e.base) + ntfy->reply;

	ret = nvif_client_ioctl(client, argv, argc);
done:
	if (ret) {
		atomic_set(&ntfy->enabled, 0);
		kfree(ntfy->p);
	}
	return ret;
}