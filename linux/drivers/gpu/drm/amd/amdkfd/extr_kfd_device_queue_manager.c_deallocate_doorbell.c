#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
struct queue {int /*<<< orphan*/  doorbell_id; TYPE_3__ properties; } ;
struct qcm_process_device {int /*<<< orphan*/  doorbell_bitmap; TYPE_1__* dqm; } ;
struct kfd_dev {TYPE_2__* device_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  asic_family; } ;
struct TYPE_4__ {struct kfd_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KFD_IS_SOC15 (int /*<<< orphan*/ ) ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA_XGMI ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void deallocate_doorbell(struct qcm_process_device *qpd,
				struct queue *q)
{
	unsigned int old;
	struct kfd_dev *dev = qpd->dqm->dev;

	if (!KFD_IS_SOC15(dev->device_info->asic_family) ||
	    q->properties.type == KFD_QUEUE_TYPE_SDMA ||
	    q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
		return;

	old = test_and_clear_bit(q->doorbell_id, qpd->doorbell_bitmap);
	WARN_ON(!old);
}