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
struct rxe_queue_buf {int dummy; } ;
struct rxe_queue {scalar_t__ buf_size; TYPE_1__* buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

inline void rxe_queue_reset(struct rxe_queue *q)
{
	/* queue is comprised from header and the memory
	 * of the actual queue. See "struct rxe_queue_buf" in rxe_queue.h
	 * reset only the queue itself and not the management header
	 */
	memset(q->buf->data, 0, q->buf_size - sizeof(struct rxe_queue_buf));
}