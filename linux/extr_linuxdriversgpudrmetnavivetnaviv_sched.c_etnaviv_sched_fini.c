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
struct etnaviv_gpu {int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_sched_fini (int /*<<< orphan*/ *) ; 

void etnaviv_sched_fini(struct etnaviv_gpu *gpu)
{
	drm_sched_fini(&gpu->sched);
}