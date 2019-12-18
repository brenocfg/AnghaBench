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
struct cx18_stream {int /*<<< orphan*/  q_free; int /*<<< orphan*/  q_full; int /*<<< orphan*/  q_busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx18_queue_flush (struct cx18_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void cx18_flush_queues(struct cx18_stream *s)
{
	cx18_queue_flush(s, &s->q_busy, &s->q_free);
	cx18_queue_flush(s, &s->q_full, &s->q_free);
}