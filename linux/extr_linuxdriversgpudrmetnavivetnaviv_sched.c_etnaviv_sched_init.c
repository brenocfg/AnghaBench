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
struct etnaviv_gpu {int /*<<< orphan*/  dev; int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int drm_sched_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etnaviv_hw_jobs_limit ; 
 int /*<<< orphan*/  etnaviv_job_hang_limit ; 
 int /*<<< orphan*/  etnaviv_sched_ops ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 

int etnaviv_sched_init(struct etnaviv_gpu *gpu)
{
	int ret;

	ret = drm_sched_init(&gpu->sched, &etnaviv_sched_ops,
			     etnaviv_hw_jobs_limit, etnaviv_job_hang_limit,
			     msecs_to_jiffies(500), dev_name(gpu->dev));
	if (ret)
		return ret;

	return 0;
}