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
struct vb2_queue {int error; int /*<<< orphan*/  done_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void vb2_queue_error(struct vb2_queue *q)
{
	q->error = 1;

	wake_up_all(&q->done_wq);
}