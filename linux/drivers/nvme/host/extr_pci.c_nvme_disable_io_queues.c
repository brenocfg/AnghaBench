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
struct nvme_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ __nvme_disable_io_queues (struct nvme_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_admin_delete_cq ; 
 int /*<<< orphan*/  nvme_admin_delete_sq ; 

__attribute__((used)) static void nvme_disable_io_queues(struct nvme_dev *dev)
{
	if (__nvme_disable_io_queues(dev, nvme_admin_delete_sq))
		__nvme_disable_io_queues(dev, nvme_admin_delete_cq);
}