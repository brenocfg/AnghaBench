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
typedef  int /*<<< orphan*/  u32 ;
struct usif_notify {int dummy; } ;
struct nvif_ioctl_ntfy_del_v0 {int /*<<< orphan*/  index; } ;
struct nvif_client {int dummy; } ;
struct nouveau_cli {struct nvif_client base; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOSYS ; 
 struct nouveau_cli* nouveau_cli (struct drm_file*) ; 
 int nvif_client_ioctl (struct nvif_client*,void*,int /*<<< orphan*/ ) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_ioctl_ntfy_del_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usif_notify_dtor (struct usif_notify*) ; 
 struct usif_notify* usif_notify_find (struct drm_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
usif_notify_del(struct drm_file *f, void *data, u32 size, void *argv, u32 argc)
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

	ret = nvif_client_ioctl(client, argv, argc);
	if (ret == 0)
		usif_notify_dtor(ntfy);
	return ret;
}