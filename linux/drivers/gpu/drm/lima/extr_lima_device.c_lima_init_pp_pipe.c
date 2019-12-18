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
struct lima_sched_pipe {struct lima_ip* bcast_mmu; struct lima_ip* bcast_processor; int /*<<< orphan*/  num_l2_cache; struct lima_ip** l2_cache; int /*<<< orphan*/  num_processor; struct lima_ip** processor; int /*<<< orphan*/  num_mmu; struct lima_ip** mmu; } ;
struct lima_ip {scalar_t__ present; } ;
struct lima_device {scalar_t__ id; struct lima_ip* ip; struct lima_sched_pipe* pipe; } ;

/* Variables and functions */
 int LIMA_SCHED_PIPE_MAX_PROCESSOR ; 
 scalar_t__ lima_gpu_mali400 ; 
 size_t lima_ip_bcast ; 
 int lima_ip_l2_cache0 ; 
 int lima_ip_l2_cache1 ; 
 int lima_ip_pp0 ; 
 int lima_ip_pp_bcast ; 
 int lima_ip_ppmmu0 ; 
 int lima_ip_ppmmu_bcast ; 
 int lima_pipe_pp ; 
 int lima_pp_pipe_init (struct lima_device*) ; 
 int /*<<< orphan*/  lima_sched_pipe_fini (struct lima_sched_pipe*) ; 
 int lima_sched_pipe_init (struct lima_sched_pipe*,char*) ; 

__attribute__((used)) static int lima_init_pp_pipe(struct lima_device *dev)
{
	struct lima_sched_pipe *pipe = dev->pipe + lima_pipe_pp;
	int err, i;

	err = lima_sched_pipe_init(pipe, "pp");
	if (err)
		return err;

	for (i = 0; i < LIMA_SCHED_PIPE_MAX_PROCESSOR; i++) {
		struct lima_ip *pp = dev->ip + lima_ip_pp0 + i;
		struct lima_ip *ppmmu = dev->ip + lima_ip_ppmmu0 + i;
		struct lima_ip *l2_cache;

		if (dev->id == lima_gpu_mali400)
			l2_cache = dev->ip + lima_ip_l2_cache0;
		else
			l2_cache = dev->ip + lima_ip_l2_cache1 + (i >> 2);

		if (pp->present && ppmmu->present && l2_cache->present) {
			pipe->mmu[pipe->num_mmu++] = ppmmu;
			pipe->processor[pipe->num_processor++] = pp;
			if (!pipe->l2_cache[i >> 2])
				pipe->l2_cache[pipe->num_l2_cache++] = l2_cache;
		}
	}

	if (dev->ip[lima_ip_bcast].present) {
		pipe->bcast_processor = dev->ip + lima_ip_pp_bcast;
		pipe->bcast_mmu = dev->ip + lima_ip_ppmmu_bcast;
	}

	err = lima_pp_pipe_init(dev);
	if (err) {
		lima_sched_pipe_fini(pipe);
		return err;
	}

	return 0;
}