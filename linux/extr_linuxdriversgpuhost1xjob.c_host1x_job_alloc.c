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
typedef  int u64 ;
typedef  int u32 ;
struct host1x_reloc {int dummy; } ;
struct host1x_job_unpin_data {int dummy; } ;
struct host1x_job_gather {int dummy; } ;
struct host1x_job {int /*<<< orphan*/ * addr_phys; int /*<<< orphan*/ * gather_addr_phys; int /*<<< orphan*/ * reloc_addr_phys; void* gathers; void* unpins; void* relocs; struct host1x_channel* channel; int /*<<< orphan*/  ref; } ;
struct host1x_channel {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ULONG_MAX ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct host1x_job* kzalloc (int,int /*<<< orphan*/ ) ; 

struct host1x_job *host1x_job_alloc(struct host1x_channel *ch,
				    u32 num_cmdbufs, u32 num_relocs)
{
	struct host1x_job *job = NULL;
	unsigned int num_unpins = num_cmdbufs + num_relocs;
	u64 total;
	void *mem;

	/* Check that we're not going to overflow */
	total = sizeof(struct host1x_job) +
		(u64)num_relocs * sizeof(struct host1x_reloc) +
		(u64)num_unpins * sizeof(struct host1x_job_unpin_data) +
		(u64)num_cmdbufs * sizeof(struct host1x_job_gather) +
		(u64)num_unpins * sizeof(dma_addr_t) +
		(u64)num_unpins * sizeof(u32 *);
	if (total > ULONG_MAX)
		return NULL;

	mem = job = kzalloc(total, GFP_KERNEL);
	if (!job)
		return NULL;

	kref_init(&job->ref);
	job->channel = ch;

	/* Redistribute memory to the structs  */
	mem += sizeof(struct host1x_job);
	job->relocs = num_relocs ? mem : NULL;
	mem += num_relocs * sizeof(struct host1x_reloc);
	job->unpins = num_unpins ? mem : NULL;
	mem += num_unpins * sizeof(struct host1x_job_unpin_data);
	job->gathers = num_cmdbufs ? mem : NULL;
	mem += num_cmdbufs * sizeof(struct host1x_job_gather);
	job->addr_phys = num_unpins ? mem : NULL;

	job->reloc_addr_phys = job->addr_phys;
	job->gather_addr_phys = &job->addr_phys[num_relocs];

	return job;
}