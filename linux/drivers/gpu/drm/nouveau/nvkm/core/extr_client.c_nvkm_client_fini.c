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
struct nvkm_object {int dummy; } ;
struct nvkm_client {int /*<<< orphan*/  notify; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvif_debug (struct nvkm_object*,char*,char const*) ; 
 struct nvkm_client* nvkm_client (struct nvkm_object*) ; 
 int /*<<< orphan*/  nvkm_client_notify_put (struct nvkm_client*,int) ; 

__attribute__((used)) static int
nvkm_client_fini(struct nvkm_object *object, bool suspend)
{
	struct nvkm_client *client = nvkm_client(object);
	const char *name[2] = { "fini", "suspend" };
	int i;
	nvif_debug(object, "%s notify\n", name[suspend]);
	for (i = 0; i < ARRAY_SIZE(client->notify); i++)
		nvkm_client_notify_put(client, i);
	return 0;
}