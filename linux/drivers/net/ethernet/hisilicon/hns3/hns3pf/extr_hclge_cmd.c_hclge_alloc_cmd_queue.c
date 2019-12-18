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
struct hclge_cmq_ring {int ring_type; struct hclge_dev* dev; } ;
struct TYPE_4__ {struct hclge_cmq_ring crq; struct hclge_cmq_ring csq; } ;
struct hclge_hw {TYPE_2__ cmq; } ;
struct hclge_dev {TYPE_1__* pdev; struct hclge_hw hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HCLGE_TYPE_CSQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int) ; 
 int hclge_alloc_cmd_desc (struct hclge_cmq_ring*) ; 

__attribute__((used)) static int hclge_alloc_cmd_queue(struct hclge_dev *hdev, int ring_type)
{
	struct hclge_hw *hw = &hdev->hw;
	struct hclge_cmq_ring *ring =
		(ring_type == HCLGE_TYPE_CSQ) ? &hw->cmq.csq : &hw->cmq.crq;
	int ret;

	ring->ring_type = ring_type;
	ring->dev = hdev;

	ret = hclge_alloc_cmd_desc(ring);
	if (ret) {
		dev_err(&hdev->pdev->dev, "descriptor %s alloc error %d\n",
			(ring_type == HCLGE_TYPE_CSQ) ? "CSQ" : "CRQ", ret);
		return ret;
	}

	return 0;
}