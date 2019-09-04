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
typedef  size_t u32 ;
struct etnaviv_gem_submit_bo {int dummy; } ;
struct etnaviv_gem_submit {size_t nr_bos; struct etnaviv_gem_submit_bo* bos; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,size_t,size_t) ; 
 int EINVAL ; 

__attribute__((used)) static int submit_bo(struct etnaviv_gem_submit *submit, u32 idx,
	struct etnaviv_gem_submit_bo **bo)
{
	if (idx >= submit->nr_bos) {
		DRM_ERROR("invalid buffer index: %u (out of %u)\n",
				idx, submit->nr_bos);
		return -EINVAL;
	}

	*bo = &submit->bos[idx];

	return 0;
}