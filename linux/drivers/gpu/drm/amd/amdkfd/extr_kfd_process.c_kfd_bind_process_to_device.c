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
struct kfd_process_device {int dummy; } ;
struct kfd_process {int dummy; } ;
struct kfd_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct kfd_process_device* ERR_PTR (int) ; 
 struct kfd_process_device* kfd_get_process_device_data (struct kfd_dev*,struct kfd_process*) ; 
 int kfd_iommu_bind_process_to_device (struct kfd_process_device*) ; 
 int kfd_process_device_init_vm (struct kfd_process_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct kfd_process_device *kfd_bind_process_to_device(struct kfd_dev *dev,
							struct kfd_process *p)
{
	struct kfd_process_device *pdd;
	int err;

	pdd = kfd_get_process_device_data(dev, p);
	if (!pdd) {
		pr_err("Process device data doesn't exist\n");
		return ERR_PTR(-ENOMEM);
	}

	err = kfd_iommu_bind_process_to_device(pdd);
	if (err)
		return ERR_PTR(err);

	err = kfd_process_device_init_vm(pdd, NULL);
	if (err)
		return ERR_PTR(err);

	return pdd;
}