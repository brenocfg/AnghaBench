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
typedef  int /*<<< orphan*/  u32 ;
struct hl_hw_queue {int queue_type; int valid; int /*<<< orphan*/  hw_queue_id; } ;
struct hl_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 scalar_t__ HL_PAGE_SIZE ; 
 scalar_t__ HL_QUEUE_SIZE_IN_BYTES ; 
#define  QUEUE_TYPE_CPU 131 
#define  QUEUE_TYPE_EXT 130 
#define  QUEUE_TYPE_INT 129 
#define  QUEUE_TYPE_NA 128 
 int cpu_hw_queue_init (struct hl_device*,struct hl_hw_queue*) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*,int) ; 
 int ext_hw_queue_init (struct hl_device*,struct hl_hw_queue*) ; 
 int int_hw_queue_init (struct hl_device*,struct hl_hw_queue*) ; 

__attribute__((used)) static int hw_queue_init(struct hl_device *hdev, struct hl_hw_queue *q,
			u32 hw_queue_id)
{
	int rc;

	BUILD_BUG_ON(HL_QUEUE_SIZE_IN_BYTES > HL_PAGE_SIZE);

	q->hw_queue_id = hw_queue_id;

	switch (q->queue_type) {
	case QUEUE_TYPE_EXT:
		rc = ext_hw_queue_init(hdev, q);
		break;

	case QUEUE_TYPE_INT:
		rc = int_hw_queue_init(hdev, q);
		break;

	case QUEUE_TYPE_CPU:
		rc = cpu_hw_queue_init(hdev, q);
		break;

	case QUEUE_TYPE_NA:
		q->valid = 0;
		return 0;

	default:
		dev_crit(hdev->dev, "wrong queue type %d during init\n",
			q->queue_type);
		rc = -EINVAL;
		break;
	}

	if (rc)
		return rc;

	q->valid = 1;

	return 0;
}