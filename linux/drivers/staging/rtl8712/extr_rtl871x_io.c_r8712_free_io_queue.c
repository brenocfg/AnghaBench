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
struct io_queue {int /*<<< orphan*/  intf; struct io_queue* pallocated_free_ioreqs_buf; } ;
struct _adapter {struct io_queue* pio_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct io_queue*) ; 
 int /*<<< orphan*/  unregister_intf_hdl (int /*<<< orphan*/ *) ; 

void r8712_free_io_queue(struct _adapter *adapter)
{
	struct io_queue *pio_queue = adapter->pio_queue;

	if (pio_queue) {
		kfree(pio_queue->pallocated_free_ioreqs_buf);
		adapter->pio_queue = NULL;
		unregister_intf_hdl(&pio_queue->intf);
		kfree(pio_queue);
	}
}