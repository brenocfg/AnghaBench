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
struct ddcb_queue {scalar_t__ ddcb_next; scalar_t__ ddcb_act; } ;

/* Variables and functions */

__attribute__((used)) static int queue_empty(struct ddcb_queue *queue)
{
	return queue->ddcb_next == queue->ddcb_act;
}