#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  void nvkm_vmm ;
struct nvkm_object {int dummy; } ;
struct nvkm_client {int dummy; } ;
struct TYPE_3__ {void* vmm; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nvkm_object*) ; 
 struct nvkm_object* nvkm_object_search (struct nvkm_client*,int /*<<< orphan*/ ,TYPE_1__* (*) (struct nvkm_object*)) ; 
 TYPE_1__* nvkm_uvmm (struct nvkm_object*) ; 

struct nvkm_vmm *
nvkm_uvmm_search(struct nvkm_client *client, u64 handle)
{
	struct nvkm_object *object;

	object = nvkm_object_search(client, handle, &nvkm_uvmm);
	if (IS_ERR(object))
		return (void *)object;

	return nvkm_uvmm(object)->vmm;
}