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
typedef  int /*<<< orphan*/  uint32_t ;
struct kfd_topology_device {struct kfd_dev* gpu; } ;
struct kfd_dev {int dummy; } ;

/* Variables and functions */
 struct kfd_topology_device* kfd_topology_device_by_id (int /*<<< orphan*/ ) ; 

struct kfd_dev *kfd_device_by_id(uint32_t gpu_id)
{
	struct kfd_topology_device *top_dev;

	top_dev = kfd_topology_device_by_id(gpu_id);
	if (!top_dev)
		return NULL;

	return top_dev->gpu;
}