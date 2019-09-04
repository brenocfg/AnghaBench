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
struct nvkm_sclass {int dummy; } ;
struct nvkm_oclass {struct nvkm_sclass base; int /*<<< orphan*/  ctor; } ;
struct nvkm_object {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nvkm_client_child_new ; 
 struct nvkm_sclass nvkm_uclient_sclass ; 
 struct nvkm_sclass nvkm_udevice_sclass ; 

__attribute__((used)) static int
nvkm_client_child_get(struct nvkm_object *object, int index,
		      struct nvkm_oclass *oclass)
{
	const struct nvkm_sclass *sclass;

	switch (index) {
	case 0: sclass = &nvkm_uclient_sclass; break;
	case 1: sclass = &nvkm_udevice_sclass; break;
	default:
		return -EINVAL;
	}

	oclass->ctor = nvkm_client_child_new;
	oclass->base = *sclass;
	return 0;
}