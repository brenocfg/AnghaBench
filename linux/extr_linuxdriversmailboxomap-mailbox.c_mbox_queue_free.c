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
struct omap_mbox_queue {int /*<<< orphan*/  fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct omap_mbox_queue*) ; 

__attribute__((used)) static void mbox_queue_free(struct omap_mbox_queue *q)
{
	kfifo_free(&q->fifo);
	kfree(q);
}