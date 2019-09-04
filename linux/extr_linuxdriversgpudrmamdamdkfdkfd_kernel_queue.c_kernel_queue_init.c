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
struct kfd_dev {TYPE_1__* device_info; } ;
struct TYPE_4__ {scalar_t__ (* initialize ) (struct kernel_queue*,struct kfd_dev*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  rollback_packet; int /*<<< orphan*/  submit_packet; int /*<<< orphan*/  acquire_packet_buffer; int /*<<< orphan*/  uninitialize; } ;
struct kernel_queue {TYPE_2__ ops; int /*<<< orphan*/  ops_asic_specific; } ;
typedef  enum kfd_queue_type { ____Placeholder_kfd_queue_type } kfd_queue_type ;
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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KFD_KERNEL_QUEUE_SIZE ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  acquire_packet_buffer ; 
 scalar_t__ initialize (struct kernel_queue*,struct kfd_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_queue_init_cik (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_queue_init_v9 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_queue_init_vi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct kernel_queue*) ; 
 struct kernel_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rollback_packet ; 
 scalar_t__ stub1 (struct kernel_queue*,struct kfd_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_packet ; 
 int /*<<< orphan*/  uninitialize ; 

struct kernel_queue *kernel_queue_init(struct kfd_dev *dev,
					enum kfd_queue_type type)
{
	struct kernel_queue *kq;

	kq = kzalloc(sizeof(*kq), GFP_KERNEL);
	if (!kq)
		return NULL;

	kq->ops.initialize = initialize;
	kq->ops.uninitialize = uninitialize;
	kq->ops.acquire_packet_buffer = acquire_packet_buffer;
	kq->ops.submit_packet = submit_packet;
	kq->ops.rollback_packet = rollback_packet;

	switch (dev->device_info->asic_family) {
	case CHIP_CARRIZO:
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
		kernel_queue_init_vi(&kq->ops_asic_specific);
		break;

	case CHIP_KAVERI:
	case CHIP_HAWAII:
		kernel_queue_init_cik(&kq->ops_asic_specific);
		break;

	case CHIP_VEGA10:
	case CHIP_RAVEN:
		kernel_queue_init_v9(&kq->ops_asic_specific);
		break;
	default:
		WARN(1, "Unexpected ASIC family %u",
		     dev->device_info->asic_family);
		goto out_free;
	}

	if (kq->ops.initialize(kq, dev, type, KFD_KERNEL_QUEUE_SIZE))
		return kq;

	pr_err("Failed to init kernel queue\n");

out_free:
	kfree(kq);
	return NULL;
}