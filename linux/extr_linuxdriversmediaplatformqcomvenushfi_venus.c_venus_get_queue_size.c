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
struct venus_hfi_device {TYPE_1__* queues; } ;
struct hfi_queue_header {scalar_t__ write_idx; scalar_t__ read_idx; } ;
struct TYPE_2__ {struct hfi_queue_header* qhdr; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IFACEQ_NUM ; 
 int abs (scalar_t__) ; 

__attribute__((used)) static int venus_get_queue_size(struct venus_hfi_device *hdev,
				unsigned int index)
{
	struct hfi_queue_header *qhdr;

	if (index >= IFACEQ_NUM)
		return -EINVAL;

	qhdr = hdev->queues[index].qhdr;
	if (!qhdr)
		return -EINVAL;

	return abs(qhdr->read_idx - qhdr->write_idx);
}