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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {TYPE_1__* func; } ;
struct TYPE_2__ {int (* rd32 ) (struct nvkm_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ likely (int (*) (struct nvkm_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 int stub1 (struct nvkm_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
nvkm_object_rd32(struct nvkm_object *object, u64 addr, u32 *data)
{
	if (likely(object->func->rd32))
		return object->func->rd32(object, addr, data);
	return -ENODEV;
}