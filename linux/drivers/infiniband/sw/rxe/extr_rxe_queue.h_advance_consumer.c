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
struct rxe_queue {int index_mask; TYPE_1__* buf; } ;
struct TYPE_2__ {int consumer_index; } ;

/* Variables and functions */

__attribute__((used)) static inline void advance_consumer(struct rxe_queue *q)
{
	q->buf->consumer_index = (q->buf->consumer_index + 1)
			& q->index_mask;
}