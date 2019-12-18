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
typedef  int u32 ;
struct TYPE_4__ {int offset; struct host1x_bo* bo; } ;
struct TYPE_3__ {int offset; } ;
struct host1x_reloc {int shift; TYPE_2__ cmdbuf; TYPE_1__ target; } ;
struct host1x_job_gather {int offset; struct host1x_bo* bo; } ;
struct host1x_job {unsigned int num_relocs; int* reloc_addr_phys; scalar_t__ gather_copy_mapped; struct host1x_reloc* relocs; } ;
struct host1x_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_TEGRA_HOST1X_FIREWALL ; 
 int ENOMEM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 void* host1x_bo_kmap (struct host1x_bo*,int) ; 
 int /*<<< orphan*/  host1x_bo_kunmap (struct host1x_bo*,int,void*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int do_relocs(struct host1x_job *job, struct host1x_job_gather *g)
{
	u32 last_page = ~0;
	void *cmdbuf_page_addr = NULL;
	struct host1x_bo *cmdbuf = g->bo;
	unsigned int i;

	/* pin & patch the relocs for one gather */
	for (i = 0; i < job->num_relocs; i++) {
		struct host1x_reloc *reloc = &job->relocs[i];
		u32 reloc_addr = (job->reloc_addr_phys[i] +
				  reloc->target.offset) >> reloc->shift;
		u32 *target;

		/* skip all other gathers */
		if (cmdbuf != reloc->cmdbuf.bo)
			continue;

		if (IS_ENABLED(CONFIG_TEGRA_HOST1X_FIREWALL)) {
			target = (u32 *)job->gather_copy_mapped +
					reloc->cmdbuf.offset / sizeof(u32) +
						g->offset / sizeof(u32);
			goto patch_reloc;
		}

		if (last_page != reloc->cmdbuf.offset >> PAGE_SHIFT) {
			if (cmdbuf_page_addr)
				host1x_bo_kunmap(cmdbuf, last_page,
						 cmdbuf_page_addr);

			cmdbuf_page_addr = host1x_bo_kmap(cmdbuf,
					reloc->cmdbuf.offset >> PAGE_SHIFT);
			last_page = reloc->cmdbuf.offset >> PAGE_SHIFT;

			if (unlikely(!cmdbuf_page_addr)) {
				pr_err("Could not map cmdbuf for relocation\n");
				return -ENOMEM;
			}
		}

		target = cmdbuf_page_addr + (reloc->cmdbuf.offset & ~PAGE_MASK);
patch_reloc:
		*target = reloc_addr;
	}

	if (cmdbuf_page_addr)
		host1x_bo_kunmap(cmdbuf, last_page, cmdbuf_page_addr);

	return 0;
}