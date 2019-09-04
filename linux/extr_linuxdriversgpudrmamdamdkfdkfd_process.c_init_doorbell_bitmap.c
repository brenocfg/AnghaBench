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
struct qcm_process_device {int /*<<< orphan*/  doorbell_bitmap; } ;
struct TYPE_3__ {unsigned int reserved_doorbell_mask; unsigned int reserved_doorbell_val; } ;
struct kfd_dev {TYPE_1__ shared_resources; TYPE_2__* device_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  asic_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_BYTE ; 
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KFD_IS_SOC15 (int /*<<< orphan*/ ) ; 
 unsigned int KFD_MAX_NUM_OF_QUEUES_PER_PROCESS ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_doorbell_bitmap(struct qcm_process_device *qpd,
			struct kfd_dev *dev)
{
	unsigned int i;

	if (!KFD_IS_SOC15(dev->device_info->asic_family))
		return 0;

	qpd->doorbell_bitmap =
		kzalloc(DIV_ROUND_UP(KFD_MAX_NUM_OF_QUEUES_PER_PROCESS,
				     BITS_PER_BYTE), GFP_KERNEL);
	if (!qpd->doorbell_bitmap)
		return -ENOMEM;

	/* Mask out any reserved doorbells */
	for (i = 0; i < KFD_MAX_NUM_OF_QUEUES_PER_PROCESS; i++)
		if ((dev->shared_resources.reserved_doorbell_mask & i) ==
		    dev->shared_resources.reserved_doorbell_val) {
			set_bit(i, qpd->doorbell_bitmap);
			pr_debug("reserved doorbell 0x%03x\n", i);
		}

	return 0;
}