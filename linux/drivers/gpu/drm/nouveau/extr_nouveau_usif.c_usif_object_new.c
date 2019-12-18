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
struct usif_object {unsigned long token; int /*<<< orphan*/  route; int /*<<< orphan*/  head; } ;
struct nvif_ioctl_new_v0 {unsigned long token; int /*<<< orphan*/  route; } ;
struct nvif_client {int dummy; } ;
struct nouveau_cli {int /*<<< orphan*/  objects; struct nvif_client base; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVDRM_OBJECT_USIF ; 
 struct usif_object* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nouveau_cli* nouveau_cli (struct drm_file*) ; 
 int nvif_client_ioctl (struct nvif_client*,void*,int /*<<< orphan*/ ) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_ioctl_new_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usif_object_dtor (struct usif_object*) ; 

__attribute__((used)) static int
usif_object_new(struct drm_file *f, void *data, u32 size, void *argv, u32 argc)
{
	struct nouveau_cli *cli = nouveau_cli(f);
	struct nvif_client *client = &cli->base;
	union {
		struct nvif_ioctl_new_v0 v0;
	} *args = data;
	struct usif_object *object;
	int ret = -ENOSYS;

	if (!(object = kmalloc(sizeof(*object), GFP_KERNEL)))
		return -ENOMEM;
	list_add(&object->head, &cli->objects);

	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, true))) {
		object->route = args->v0.route;
		object->token = args->v0.token;
		args->v0.route = NVDRM_OBJECT_USIF;
		args->v0.token = (unsigned long)(void *)object;
		ret = nvif_client_ioctl(client, argv, argc);
		args->v0.token = object->token;
		args->v0.route = object->route;
	}

	if (ret)
		usif_object_dtor(object);
	return ret;
}