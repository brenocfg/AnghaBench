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
struct nvkm_oclass {TYPE_1__* client; int /*<<< orphan*/  object; int /*<<< orphan*/  token; int /*<<< orphan*/  route; int /*<<< orphan*/  handle; } ;
struct nvkm_object {int /*<<< orphan*/  object; int /*<<< orphan*/  token; int /*<<< orphan*/  route; int /*<<< orphan*/  handle; TYPE_1__* client; } ;
struct nvkm_client {struct nvkm_object object; int /*<<< orphan*/  debug; } ;
struct nvif_client_v0 {int /*<<< orphan*/  device; scalar_t__* name; } ;
struct TYPE_2__ {int /*<<< orphan*/  debug; int /*<<< orphan*/  ntfy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_client_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvkm_client_new (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nvkm_client**) ; 

__attribute__((used)) static int
nvkm_uclient_new(const struct nvkm_oclass *oclass, void *argv, u32 argc,
		 struct nvkm_object **pobject)
{
	union {
		struct nvif_client_v0 v0;
	} *args = argv;
	struct nvkm_client *client;
	int ret = -ENOSYS;

	if (!(ret = nvif_unpack(ret, &argv, &argc, args->v0, 0, 0, false))){
		args->v0.name[sizeof(args->v0.name) - 1] = 0;
		ret = nvkm_client_new(args->v0.name, args->v0.device, NULL,
				      NULL, oclass->client->ntfy, &client);
		if (ret)
			return ret;
	} else
		return ret;

	client->object.client = oclass->client;
	client->object.handle = oclass->handle;
	client->object.route  = oclass->route;
	client->object.token  = oclass->token;
	client->object.object = oclass->object;
	client->debug = oclass->client->debug;
	*pobject = &client->object;
	return 0;
}