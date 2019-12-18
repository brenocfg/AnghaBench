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
typedef  int /*<<< orphan*/  u32 ;
struct host1x_job_gather {int words; size_t offset; int /*<<< orphan*/  base; int /*<<< orphan*/  bo; } ;
struct host1x_job {unsigned int num_gathers; size_t gather_copy_size; int /*<<< orphan*/  gather_copy; void* gather_copy_mapped; struct host1x_job_gather* gathers; int /*<<< orphan*/  class; scalar_t__ num_relocs; int /*<<< orphan*/  relocs; } ;
struct host1x_firewall {scalar_t__ num_relocs; int /*<<< orphan*/  class; int /*<<< orphan*/  reloc; struct device* dev; struct host1x_job* job; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 void* dma_alloc_wc (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* host1x_bo_mmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_bo_munmap (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 scalar_t__ validate (struct host1x_firewall*,struct host1x_job_gather*) ; 

__attribute__((used)) static inline int copy_gathers(struct host1x_job *job, struct device *dev)
{
	struct host1x_firewall fw;
	size_t size = 0;
	size_t offset = 0;
	unsigned int i;

	fw.job = job;
	fw.dev = dev;
	fw.reloc = job->relocs;
	fw.num_relocs = job->num_relocs;
	fw.class = job->class;

	for (i = 0; i < job->num_gathers; i++) {
		struct host1x_job_gather *g = &job->gathers[i];

		size += g->words * sizeof(u32);
	}

	/*
	 * Try a non-blocking allocation from a higher priority pools first,
	 * as awaiting for the allocation here is a major performance hit.
	 */
	job->gather_copy_mapped = dma_alloc_wc(dev, size, &job->gather_copy,
					       GFP_NOWAIT);

	/* the higher priority allocation failed, try the generic-blocking */
	if (!job->gather_copy_mapped)
		job->gather_copy_mapped = dma_alloc_wc(dev, size,
						       &job->gather_copy,
						       GFP_KERNEL);
	if (!job->gather_copy_mapped)
		return -ENOMEM;

	job->gather_copy_size = size;

	for (i = 0; i < job->num_gathers; i++) {
		struct host1x_job_gather *g = &job->gathers[i];
		void *gather;

		/* Copy the gather */
		gather = host1x_bo_mmap(g->bo);
		memcpy(job->gather_copy_mapped + offset, gather + g->offset,
		       g->words * sizeof(u32));
		host1x_bo_munmap(g->bo, gather);

		/* Store the location in the buffer */
		g->base = job->gather_copy;
		g->offset = offset;

		/* Validate the job */
		if (validate(&fw, g))
			return -EINVAL;

		offset += g->words * sizeof(u32);
	}

	/* No relocs should remain at this point */
	if (fw.num_relocs)
		return -EINVAL;

	return 0;
}