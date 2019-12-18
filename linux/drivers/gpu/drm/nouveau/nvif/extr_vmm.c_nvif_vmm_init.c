#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  scalar_t__ u32 ;
struct nvif_vmm_v0 {int managed; int page_nr; void* size; void* addr; int /*<<< orphan*/  data; scalar_t__ version; } ;
struct nvif_vmm_page_v0 {int index; int /*<<< orphan*/  comp; int /*<<< orphan*/  host; int /*<<< orphan*/  vram; int /*<<< orphan*/  sparse; int /*<<< orphan*/  shift; } ;
struct TYPE_4__ {int /*<<< orphan*/ * client; } ;
struct nvif_vmm {int page_nr; TYPE_3__* page; TYPE_1__ object; void* limit; void* start; } ;
struct nvif_mmu {int /*<<< orphan*/  object; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_5__ {int /*<<< orphan*/  comp; int /*<<< orphan*/  host; int /*<<< orphan*/  vram; int /*<<< orphan*/  sparse; int /*<<< orphan*/  shift; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVIF_VMM_V0_PAGE ; 
 int /*<<< orphan*/  kfree (struct nvif_vmm_v0*) ; 
 struct nvif_vmm_v0* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int nvif_object_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvif_vmm_v0*,scalar_t__,TYPE_1__*) ; 
 int nvif_object_mthd (TYPE_1__*,int /*<<< orphan*/ ,struct nvif_vmm_page_v0*,int) ; 
 int /*<<< orphan*/  nvif_vmm_fini (struct nvif_vmm*) ; 

int
nvif_vmm_init(struct nvif_mmu *mmu, s32 oclass, bool managed, u64 addr,
	      u64 size, void *argv, u32 argc, struct nvif_vmm *vmm)
{
	struct nvif_vmm_v0 *args;
	u32 argn = sizeof(*args) + argc;
	int ret = -ENOSYS, i;

	vmm->object.client = NULL;
	vmm->page = NULL;

	if (!(args = kmalloc(argn, GFP_KERNEL)))
		return -ENOMEM;
	args->version = 0;
	args->managed = managed;
	args->addr = addr;
	args->size = size;
	memcpy(args->data, argv, argc);

	ret = nvif_object_init(&mmu->object, 0, oclass, args, argn,
			       &vmm->object);
	if (ret)
		goto done;

	vmm->start = args->addr;
	vmm->limit = args->size;

	vmm->page_nr = args->page_nr;
	vmm->page = kmalloc_array(vmm->page_nr, sizeof(*vmm->page),
				  GFP_KERNEL);
	if (!vmm->page) {
		ret = -ENOMEM;
		goto done;
	}

	for (i = 0; i < vmm->page_nr; i++) {
		struct nvif_vmm_page_v0 args = { .index = i };

		ret = nvif_object_mthd(&vmm->object, NVIF_VMM_V0_PAGE,
				       &args, sizeof(args));
		if (ret)
			break;

		vmm->page[i].shift = args.shift;
		vmm->page[i].sparse = args.sparse;
		vmm->page[i].vram = args.vram;
		vmm->page[i].host = args.host;
		vmm->page[i].comp = args.comp;
	}

done:
	if (ret)
		nvif_vmm_fini(vmm);
	kfree(args);
	return ret;
}