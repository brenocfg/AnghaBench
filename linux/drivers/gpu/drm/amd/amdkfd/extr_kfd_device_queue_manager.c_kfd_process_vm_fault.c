#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kfd_process_device {int /*<<< orphan*/  qpd; } ;
struct kfd_process {int dummy; } ;
struct TYPE_2__ {int (* evict_process_queues ) (struct device_queue_manager*,int /*<<< orphan*/ *) ;} ;
struct device_queue_manager {TYPE_1__ ops; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct kfd_process_device* kfd_get_process_device_data (int /*<<< orphan*/ ,struct kfd_process*) ; 
 struct kfd_process* kfd_lookup_process_by_pasid (unsigned int) ; 
 int /*<<< orphan*/  kfd_unref_process (struct kfd_process*) ; 
 int stub1 (struct device_queue_manager*,int /*<<< orphan*/ *) ; 

int kfd_process_vm_fault(struct device_queue_manager *dqm,
			 unsigned int pasid)
{
	struct kfd_process_device *pdd;
	struct kfd_process *p = kfd_lookup_process_by_pasid(pasid);
	int ret = 0;

	if (!p)
		return -EINVAL;
	pdd = kfd_get_process_device_data(dqm->dev, p);
	if (pdd)
		ret = dqm->ops.evict_process_queues(dqm, &pdd->qpd);
	kfd_unref_process(p);

	return ret;
}