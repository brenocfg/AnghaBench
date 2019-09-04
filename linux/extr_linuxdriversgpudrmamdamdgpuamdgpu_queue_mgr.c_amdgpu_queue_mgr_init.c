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
struct amdgpu_queue_mgr {int /*<<< orphan*/ * mapper; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int AMDGPU_MAX_IP_NUM ; 
 int EINVAL ; 
 int amdgpu_queue_mapper_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct amdgpu_queue_mgr*,int /*<<< orphan*/ ,int) ; 

int amdgpu_queue_mgr_init(struct amdgpu_device *adev,
			  struct amdgpu_queue_mgr *mgr)
{
	int i, r;

	if (!adev || !mgr)
		return -EINVAL;

	memset(mgr, 0, sizeof(*mgr));

	for (i = 0; i < AMDGPU_MAX_IP_NUM; ++i) {
		r = amdgpu_queue_mapper_init(&mgr->mapper[i], i);
		if (r)
			return r;
	}

	return 0;
}