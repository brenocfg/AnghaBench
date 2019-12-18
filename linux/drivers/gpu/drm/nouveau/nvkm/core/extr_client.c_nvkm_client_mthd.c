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
typedef  int u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVIF_CLIENT_V0_DEVLIST 128 
 struct nvkm_client* nvkm_client (struct nvkm_object*) ; 
 int nvkm_client_mthd_devlist (struct nvkm_client*,void*,int) ; 

__attribute__((used)) static int
nvkm_client_mthd(struct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	struct nvkm_client *client = nvkm_client(object);
	switch (mthd) {
	case NVIF_CLIENT_V0_DEVLIST:
		return nvkm_client_mthd_devlist(client, data, size);
	default:
		break;
	}
	return -EINVAL;
}