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
struct qdio_q {int dummy; } ;
struct qdio_irq {struct qdio_q** output_qs; struct qdio_q** input_qs; } ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {struct qdio_irq* qdio_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int __qdio_inspect_queue (struct qdio_q*,unsigned int*,unsigned int*) ; 
 scalar_t__ need_siga_sync (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_siga_sync_q (struct qdio_q*) ; 

int qdio_inspect_queue(struct ccw_device *cdev, unsigned int nr, bool is_input,
		       unsigned int *bufnr, unsigned int *error)
{
	struct qdio_irq *irq_ptr = cdev->private->qdio_data;
	struct qdio_q *q;

	if (!irq_ptr)
		return -ENODEV;
	q = is_input ? irq_ptr->input_qs[nr] : irq_ptr->output_qs[nr];

	if (need_siga_sync(q))
		qdio_siga_sync_q(q);

	return __qdio_inspect_queue(q, bufnr, error);
}