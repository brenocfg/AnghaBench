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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_falcon {int /*<<< orphan*/  dmem_mutex; TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_dmem ) (struct nvkm_falcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_falcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void
nvkm_falcon_read_dmem(struct nvkm_falcon *falcon, u32 start, u32 size, u8 port,
		      void *data)
{
	mutex_lock(&falcon->dmem_mutex);

	falcon->func->read_dmem(falcon, start, size, port, data);

	mutex_unlock(&falcon->dmem_mutex);
}