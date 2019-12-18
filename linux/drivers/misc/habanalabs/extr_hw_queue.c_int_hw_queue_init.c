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
typedef  scalar_t__ u64 ;
struct hl_hw_queue {scalar_t__ ci; scalar_t__ pi; scalar_t__ kernel_address; int /*<<< orphan*/  hw_queue_id; int /*<<< orphan*/  int_queue_len; int /*<<< orphan*/  bus_address; } ;
struct hl_device {int /*<<< orphan*/  dev; TYPE_1__* asic_funcs; } ;
struct TYPE_2__ {void* (* get_int_queue_base ) (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* stub1 (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int int_hw_queue_init(struct hl_device *hdev, struct hl_hw_queue *q)
{
	void *p;

	p = hdev->asic_funcs->get_int_queue_base(hdev, q->hw_queue_id,
					&q->bus_address, &q->int_queue_len);
	if (!p) {
		dev_err(hdev->dev,
			"Failed to get base address for internal queue %d\n",
			q->hw_queue_id);
		return -EFAULT;
	}

	q->kernel_address = (u64) (uintptr_t) p;
	q->pi = 0;
	q->ci = 0;

	return 0;
}