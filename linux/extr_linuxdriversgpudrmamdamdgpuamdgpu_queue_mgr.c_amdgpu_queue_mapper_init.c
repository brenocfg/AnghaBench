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
struct amdgpu_queue_mapper {int hw_ip; int /*<<< orphan*/  queue_map; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int AMDGPU_MAX_IP_NUM ; 
 int EINVAL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_queue_mapper_init(struct amdgpu_queue_mapper *mapper,
				    int hw_ip)
{
	if (!mapper)
		return -EINVAL;

	if (hw_ip > AMDGPU_MAX_IP_NUM)
		return -EINVAL;

	mapper->hw_ip = hw_ip;
	mutex_init(&mapper->lock);

	memset(mapper->queue_map, 0, sizeof(mapper->queue_map));

	return 0;
}