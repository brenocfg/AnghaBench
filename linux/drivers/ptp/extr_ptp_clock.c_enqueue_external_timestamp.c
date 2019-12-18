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
typedef  int /*<<< orphan*/  u32 ;
struct timestamp_event_queue {size_t tail; int head; int /*<<< orphan*/  lock; struct ptp_extts_event* buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  nsec; int /*<<< orphan*/  sec; } ;
struct ptp_extts_event {TYPE_1__ t; int /*<<< orphan*/  index; } ;
struct ptp_clock_event {int /*<<< orphan*/  index; int /*<<< orphan*/  timestamp; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int PTP_MAX_TIMESTAMPS ; 
 int /*<<< orphan*/  div_u64_rem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_free (struct timestamp_event_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void enqueue_external_timestamp(struct timestamp_event_queue *queue,
				       struct ptp_clock_event *src)
{
	struct ptp_extts_event *dst;
	unsigned long flags;
	s64 seconds;
	u32 remainder;

	seconds = div_u64_rem(src->timestamp, 1000000000, &remainder);

	spin_lock_irqsave(&queue->lock, flags);

	dst = &queue->buf[queue->tail];
	dst->index = src->index;
	dst->t.sec = seconds;
	dst->t.nsec = remainder;

	if (!queue_free(queue))
		queue->head = (queue->head + 1) % PTP_MAX_TIMESTAMPS;

	queue->tail = (queue->tail + 1) % PTP_MAX_TIMESTAMPS;

	spin_unlock_irqrestore(&queue->lock, flags);
}