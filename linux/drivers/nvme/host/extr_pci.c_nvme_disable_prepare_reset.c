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
struct nvme_dev {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  nvme_dev_disable (struct nvme_dev*,int) ; 
 int /*<<< orphan*/  nvme_wait_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_disable_prepare_reset(struct nvme_dev *dev, bool shutdown)
{
	if (!nvme_wait_reset(&dev->ctrl))
		return -EBUSY;
	nvme_dev_disable(dev, shutdown);
	return 0;
}