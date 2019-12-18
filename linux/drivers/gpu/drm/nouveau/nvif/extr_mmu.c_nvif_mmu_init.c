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
struct nvif_object {int dummy; } ;
struct nvif_mmu_v0 {int heap_nr; int type_nr; int kind_nr; int /*<<< orphan*/  dmabits; scalar_t__ version; } ;
struct nvif_mmu_type_v0 {int index; int count; int /*<<< orphan*/  data; scalar_t__ version; int /*<<< orphan*/  heap; scalar_t__ uncached; scalar_t__ coherent; scalar_t__ mappable; scalar_t__ kind; scalar_t__ disp; scalar_t__ comp; scalar_t__ host; scalar_t__ vram; int /*<<< orphan*/  size; } ;
struct nvif_mmu_kind_v0 {int index; int count; int /*<<< orphan*/  data; scalar_t__ version; int /*<<< orphan*/  heap; scalar_t__ uncached; scalar_t__ coherent; scalar_t__ mappable; scalar_t__ kind; scalar_t__ disp; scalar_t__ comp; scalar_t__ host; scalar_t__ vram; int /*<<< orphan*/  size; } ;
struct nvif_mmu_heap_v0 {int index; int count; int /*<<< orphan*/  data; scalar_t__ version; int /*<<< orphan*/  heap; scalar_t__ uncached; scalar_t__ coherent; scalar_t__ mappable; scalar_t__ kind; scalar_t__ disp; scalar_t__ comp; scalar_t__ host; scalar_t__ vram; int /*<<< orphan*/  size; } ;
struct nvif_mmu {int heap_nr; int type_nr; int kind_nr; int /*<<< orphan*/ * kind; int /*<<< orphan*/  object; TYPE_2__* type; TYPE_1__* heap; int /*<<< orphan*/  mem; int /*<<< orphan*/  dmabits; } ;
struct nvif_mclass {int member_1; int /*<<< orphan*/  oclass; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_4__ {int /*<<< orphan*/  heap; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  NVIF_CLASS_MEM_GF100 130 
#define  NVIF_CLASS_MEM_NV04 129 
#define  NVIF_CLASS_MEM_NV50 128 
 int /*<<< orphan*/  NVIF_MEM_COHERENT ; 
 int /*<<< orphan*/  NVIF_MEM_COMP ; 
 int /*<<< orphan*/  NVIF_MEM_DISP ; 
 int /*<<< orphan*/  NVIF_MEM_HOST ; 
 int /*<<< orphan*/  NVIF_MEM_KIND ; 
 int /*<<< orphan*/  NVIF_MEM_MAPPABLE ; 
 int /*<<< orphan*/  NVIF_MEM_UNCACHED ; 
 int /*<<< orphan*/  NVIF_MEM_VRAM ; 
 int /*<<< orphan*/  NVIF_MMU_V0_HEAP ; 
 int /*<<< orphan*/  NVIF_MMU_V0_KIND ; 
 int /*<<< orphan*/  NVIF_MMU_V0_TYPE ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  kfree (struct nvif_mmu_type_v0*) ; 
 struct nvif_mmu_type_v0* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 void* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nvif_mclass (int /*<<< orphan*/ *,struct nvif_mclass const*) ; 
 int /*<<< orphan*/  nvif_mmu_fini (struct nvif_mmu*) ; 
 int nvif_object_init (struct nvif_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvif_mmu_v0*,int,int /*<<< orphan*/ *) ; 
 int nvif_object_mthd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nvif_mmu_type_v0*,size_t) ; 
 size_t struct_size (struct nvif_mmu_type_v0*,int /*<<< orphan*/ ,int) ; 

int
nvif_mmu_init(struct nvif_object *parent, s32 oclass, struct nvif_mmu *mmu)
{
	static const struct nvif_mclass mems[] = {
		{ NVIF_CLASS_MEM_GF100, -1 },
		{ NVIF_CLASS_MEM_NV50 , -1 },
		{ NVIF_CLASS_MEM_NV04 , -1 },
		{}
	};
	struct nvif_mmu_v0 args;
	int ret, i;

	args.version = 0;
	mmu->heap = NULL;
	mmu->type = NULL;
	mmu->kind = NULL;

	ret = nvif_object_init(parent, 0, oclass, &args, sizeof(args),
			       &mmu->object);
	if (ret)
		goto done;

	mmu->dmabits = args.dmabits;
	mmu->heap_nr = args.heap_nr;
	mmu->type_nr = args.type_nr;
	mmu->kind_nr = args.kind_nr;

	ret = nvif_mclass(&mmu->object, mems);
	if (ret < 0)
		goto done;
	mmu->mem = mems[ret].oclass;

	mmu->heap = kmalloc_array(mmu->heap_nr, sizeof(*mmu->heap),
				  GFP_KERNEL);
	mmu->type = kmalloc_array(mmu->type_nr, sizeof(*mmu->type),
				  GFP_KERNEL);
	if (ret = -ENOMEM, !mmu->heap || !mmu->type)
		goto done;

	mmu->kind = kmalloc_array(mmu->kind_nr, sizeof(*mmu->kind),
				  GFP_KERNEL);
	if (!mmu->kind && mmu->kind_nr)
		goto done;

	for (i = 0; i < mmu->heap_nr; i++) {
		struct nvif_mmu_heap_v0 args = { .index = i };

		ret = nvif_object_mthd(&mmu->object, NVIF_MMU_V0_HEAP,
				       &args, sizeof(args));
		if (ret)
			goto done;

		mmu->heap[i].size = args.size;
	}

	for (i = 0; i < mmu->type_nr; i++) {
		struct nvif_mmu_type_v0 args = { .index = i };

		ret = nvif_object_mthd(&mmu->object, NVIF_MMU_V0_TYPE,
				       &args, sizeof(args));
		if (ret)
			goto done;

		mmu->type[i].type = 0;
		if (args.vram) mmu->type[i].type |= NVIF_MEM_VRAM;
		if (args.host) mmu->type[i].type |= NVIF_MEM_HOST;
		if (args.comp) mmu->type[i].type |= NVIF_MEM_COMP;
		if (args.disp) mmu->type[i].type |= NVIF_MEM_DISP;
		if (args.kind    ) mmu->type[i].type |= NVIF_MEM_KIND;
		if (args.mappable) mmu->type[i].type |= NVIF_MEM_MAPPABLE;
		if (args.coherent) mmu->type[i].type |= NVIF_MEM_COHERENT;
		if (args.uncached) mmu->type[i].type |= NVIF_MEM_UNCACHED;
		mmu->type[i].heap = args.heap;
	}

	if (mmu->kind_nr) {
		struct nvif_mmu_kind_v0 *kind;
		size_t argc = struct_size(kind, data, mmu->kind_nr);

		if (ret = -ENOMEM, !(kind = kmalloc(argc, GFP_KERNEL)))
			goto done;
		kind->version = 0;
		kind->count = mmu->kind_nr;

		ret = nvif_object_mthd(&mmu->object, NVIF_MMU_V0_KIND,
				       kind, argc);
		if (ret == 0)
			memcpy(mmu->kind, kind->data, kind->count);
		kfree(kind);
	}

done:
	if (ret)
		nvif_mmu_fini(mmu);
	return ret;
}