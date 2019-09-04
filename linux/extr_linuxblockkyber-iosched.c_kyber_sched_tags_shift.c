#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct kyber_queue_data {TYPE_5__* q; } ;
struct TYPE_10__ {TYPE_4__** queue_hw_ctx; } ;
struct TYPE_9__ {TYPE_3__* sched_tags; } ;
struct TYPE_6__ {unsigned int shift; } ;
struct TYPE_7__ {TYPE_1__ sb; } ;
struct TYPE_8__ {TYPE_2__ bitmap_tags; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int kyber_sched_tags_shift(struct kyber_queue_data *kqd)
{
	/*
	 * All of the hardware queues have the same depth, so we can just grab
	 * the shift of the first one.
	 */
	return kqd->q->queue_hw_ctx[0]->sched_tags->bitmap_tags.sb.shift;
}