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
struct vnic_cq {int /*<<< orphan*/  ring; TYPE_1__* ctrl; scalar_t__ last_color; scalar_t__ to_clean; } ;
struct TYPE_2__ {int /*<<< orphan*/  cq_tail_color; int /*<<< orphan*/  cq_tail; int /*<<< orphan*/  cq_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svnic_dev_clear_desc_ring (int /*<<< orphan*/ *) ; 

void svnic_cq_clean(struct vnic_cq *cq)
{
	cq->to_clean = 0;
	cq->last_color = 0;

	iowrite32(0, &cq->ctrl->cq_head);
	iowrite32(0, &cq->ctrl->cq_tail);
	iowrite32(1, &cq->ctrl->cq_tail_color);

	svnic_dev_clear_desc_ring(&cq->ring);
}