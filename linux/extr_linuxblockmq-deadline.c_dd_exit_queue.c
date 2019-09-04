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
struct elevator_queue {struct deadline_data* elevator_data; } ;
struct deadline_data {int /*<<< orphan*/ * fifo_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t READ ; 
 size_t WRITE ; 
 int /*<<< orphan*/  kfree (struct deadline_data*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dd_exit_queue(struct elevator_queue *e)
{
	struct deadline_data *dd = e->elevator_data;

	BUG_ON(!list_empty(&dd->fifo_list[READ]));
	BUG_ON(!list_empty(&dd->fifo_list[WRITE]));

	kfree(dd);
}