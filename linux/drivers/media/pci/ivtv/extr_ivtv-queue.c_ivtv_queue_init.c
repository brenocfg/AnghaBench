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
struct ivtv_queue {scalar_t__ bytesused; scalar_t__ length; scalar_t__ buffers; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void ivtv_queue_init(struct ivtv_queue *q)
{
	INIT_LIST_HEAD(&q->list);
	q->buffers = 0;
	q->length = 0;
	q->bytesused = 0;
}