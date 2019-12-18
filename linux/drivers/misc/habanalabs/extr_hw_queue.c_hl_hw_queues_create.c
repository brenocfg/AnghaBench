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
struct hl_hw_queue {int /*<<< orphan*/  queue_type; } ;
struct asic_fixed_properties {TYPE_1__* hw_queues_props; } ;
struct hl_device {struct hl_hw_queue* kernel_queues; int /*<<< orphan*/  dev; struct asic_fixed_properties asic_prop; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HL_MAX_QUEUES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hw_queue_fini (struct hl_device*,struct hl_hw_queue*) ; 
 int hw_queue_init (struct hl_device*,struct hl_hw_queue*,int) ; 
 struct hl_hw_queue* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hl_hw_queue*) ; 

int hl_hw_queues_create(struct hl_device *hdev)
{
	struct asic_fixed_properties *asic = &hdev->asic_prop;
	struct hl_hw_queue *q;
	int i, rc, q_ready_cnt;

	hdev->kernel_queues = kcalloc(HL_MAX_QUEUES,
				sizeof(*hdev->kernel_queues), GFP_KERNEL);

	if (!hdev->kernel_queues) {
		dev_err(hdev->dev, "Not enough memory for H/W queues\n");
		return -ENOMEM;
	}

	/* Initialize the H/W queues */
	for (i = 0, q_ready_cnt = 0, q = hdev->kernel_queues;
			i < HL_MAX_QUEUES ; i++, q_ready_cnt++, q++) {

		q->queue_type = asic->hw_queues_props[i].type;
		rc = hw_queue_init(hdev, q, i);
		if (rc) {
			dev_err(hdev->dev,
				"failed to initialize queue %d\n", i);
			goto release_queues;
		}
	}

	return 0;

release_queues:
	for (i = 0, q = hdev->kernel_queues ; i < q_ready_cnt ; i++, q++)
		hw_queue_fini(hdev, q);

	kfree(hdev->kernel_queues);

	return rc;
}