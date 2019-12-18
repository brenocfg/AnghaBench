#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_8__ {unsigned int queue_id; scalar_t__ type; size_t sdma_engine_id; int sdma_queue_id; int /*<<< orphan*/  doorbell_off; } ;
struct queue {unsigned int doorbell_id; int /*<<< orphan*/  process; TYPE_4__ properties; } ;
struct qcm_process_device {int /*<<< orphan*/  doorbell_bitmap; TYPE_1__* dqm; } ;
struct TYPE_7__ {unsigned int* sdma_doorbell_idx; } ;
struct kfd_dev {TYPE_3__ shared_resources; TYPE_2__* device_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  asic_family; } ;
struct TYPE_5__ {struct kfd_dev* dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KFD_IS_SOC15 (int /*<<< orphan*/ ) ; 
 unsigned int KFD_MAX_NUM_OF_QUEUES_PER_PROCESS ; 
 int KFD_QUEUE_DOORBELL_MIRROR_OFFSET ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA ; 
 scalar_t__ KFD_QUEUE_TYPE_SDMA_XGMI ; 
 unsigned int find_first_zero_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfd_doorbell_id_to_offset (struct kfd_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allocate_doorbell(struct qcm_process_device *qpd, struct queue *q)
{
	struct kfd_dev *dev = qpd->dqm->dev;

	if (!KFD_IS_SOC15(dev->device_info->asic_family)) {
		/* On pre-SOC15 chips we need to use the queue ID to
		 * preserve the user mode ABI.
		 */
		q->doorbell_id = q->properties.queue_id;
	} else if (q->properties.type == KFD_QUEUE_TYPE_SDMA ||
			q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI) {
		/* For SDMA queues on SOC15 with 8-byte doorbell, use static
		 * doorbell assignments based on the engine and queue id.
		 * The doobell index distance between RLC (2*i) and (2*i+1)
		 * for a SDMA engine is 512.
		 */
		uint32_t *idx_offset =
				dev->shared_resources.sdma_doorbell_idx;

		q->doorbell_id = idx_offset[q->properties.sdma_engine_id]
			+ (q->properties.sdma_queue_id & 1)
			* KFD_QUEUE_DOORBELL_MIRROR_OFFSET
			+ (q->properties.sdma_queue_id >> 1);
	} else {
		/* For CP queues on SOC15 reserve a free doorbell ID */
		unsigned int found;

		found = find_first_zero_bit(qpd->doorbell_bitmap,
					    KFD_MAX_NUM_OF_QUEUES_PER_PROCESS);
		if (found >= KFD_MAX_NUM_OF_QUEUES_PER_PROCESS) {
			pr_debug("No doorbells available");
			return -EBUSY;
		}
		set_bit(found, qpd->doorbell_bitmap);
		q->doorbell_id = found;
	}

	q->properties.doorbell_off =
		kfd_doorbell_id_to_offset(dev, q->process,
					  q->doorbell_id);

	return 0;
}