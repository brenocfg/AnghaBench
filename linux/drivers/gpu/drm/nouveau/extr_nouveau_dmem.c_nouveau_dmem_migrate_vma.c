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
struct vm_area_struct {int dummy; } ;
struct nouveau_drm {int dummy; } ;
struct migrate_vma {unsigned long start; unsigned long end; int /*<<< orphan*/ * src; int /*<<< orphan*/ * dst; scalar_t__ cpages; struct vm_area_struct* vma; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  SG_MAX_SINGLE_ALLOC ; 
 void* kcalloc (unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (unsigned long,int,int /*<<< orphan*/ ) ; 
 int migrate_vma_setup (struct migrate_vma*) ; 
 unsigned long min (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  nouveau_dmem_migrate_chunk (struct nouveau_drm*,struct migrate_vma*,int /*<<< orphan*/ *) ; 

int
nouveau_dmem_migrate_vma(struct nouveau_drm *drm,
			 struct vm_area_struct *vma,
			 unsigned long start,
			 unsigned long end)
{
	unsigned long npages = (end - start) >> PAGE_SHIFT;
	unsigned long max = min(SG_MAX_SINGLE_ALLOC, npages);
	dma_addr_t *dma_addrs;
	struct migrate_vma args = {
		.vma		= vma,
		.start		= start,
	};
	unsigned long c, i;
	int ret = -ENOMEM;

	args.src = kcalloc(max, sizeof(args.src), GFP_KERNEL);
	if (!args.src)
		goto out;
	args.dst = kcalloc(max, sizeof(args.dst), GFP_KERNEL);
	if (!args.dst)
		goto out_free_src;

	dma_addrs = kmalloc_array(max, sizeof(*dma_addrs), GFP_KERNEL);
	if (!dma_addrs)
		goto out_free_dst;

	for (i = 0; i < npages; i += c) {
		c = min(SG_MAX_SINGLE_ALLOC, npages);
		args.end = start + (c << PAGE_SHIFT);
		ret = migrate_vma_setup(&args);
		if (ret)
			goto out_free_dma;

		if (args.cpages)
			nouveau_dmem_migrate_chunk(drm, &args, dma_addrs);
		args.start = args.end;
	}

	ret = 0;
out_free_dma:
	kfree(dma_addrs);
out_free_dst:
	kfree(args.dst);
out_free_src:
	kfree(args.src);
out:
	return ret;
}