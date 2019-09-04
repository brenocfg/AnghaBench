#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct packet_manager {int allocated; int /*<<< orphan*/  lock; int /*<<< orphan*/  priv_queue; struct device_queue_manager* dqm; int /*<<< orphan*/ * pmf; } ;
struct device_queue_manager {TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* device_info; } ;
struct TYPE_3__ {int asic_family; } ;

/* Variables and functions */
#define  CHIP_CARRIZO 136 
#define  CHIP_FIJI 135 
#define  CHIP_HAWAII 134 
#define  CHIP_KAVERI 133 
#define  CHIP_POLARIS10 132 
#define  CHIP_POLARIS11 131 
#define  CHIP_RAVEN 130 
#define  CHIP_TONGA 129 
#define  CHIP_VEGA10 128 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KFD_QUEUE_TYPE_HIQ ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  kernel_queue_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfd_v9_pm_funcs ; 
 int /*<<< orphan*/  kfd_vi_pm_funcs ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int pm_init(struct packet_manager *pm, struct device_queue_manager *dqm)
{
	switch (dqm->dev->device_info->asic_family) {
	case CHIP_KAVERI:
	case CHIP_HAWAII:
		/* PM4 packet structures on CIK are the same as on VI */
	case CHIP_CARRIZO:
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
		pm->pmf = &kfd_vi_pm_funcs;
		break;
	case CHIP_VEGA10:
	case CHIP_RAVEN:
		pm->pmf = &kfd_v9_pm_funcs;
		break;
	default:
		WARN(1, "Unexpected ASIC family %u",
		     dqm->dev->device_info->asic_family);
		return -EINVAL;
	}

	pm->dqm = dqm;
	mutex_init(&pm->lock);
	pm->priv_queue = kernel_queue_init(dqm->dev, KFD_QUEUE_TYPE_HIQ);
	if (!pm->priv_queue) {
		mutex_destroy(&pm->lock);
		return -ENOMEM;
	}
	pm->allocated = false;

	return 0;
}