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
struct ddcb_queue {int /*<<< orphan*/ * ddcb_vaddr; } ;

/* Variables and functions */

__attribute__((used)) static int ddcb_queue_initialized(struct ddcb_queue *queue)
{
	return queue->ddcb_vaddr != NULL;
}