#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_memory {int dummy; } ;
struct nv40_instobj {TYPE_2__* node; TYPE_1__* imem; } ;
struct TYPE_4__ {scalar_t__ offset; } ;
struct TYPE_3__ {scalar_t__ iomem; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32_native (int /*<<< orphan*/ ,scalar_t__) ; 
 struct nv40_instobj* nv40_instobj (struct nvkm_memory*) ; 

__attribute__((used)) static void
nv40_instobj_wr32(struct nvkm_memory *memory, u64 offset, u32 data)
{
	struct nv40_instobj *iobj = nv40_instobj(memory);
	iowrite32_native(data, iobj->imem->iomem + iobj->node->offset + offset);
}