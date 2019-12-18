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
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct io_req {int /*<<< orphan*/  list; } ;
struct io_queue {struct io_queue* pallocated_free_ioreqs_buf; int /*<<< orphan*/  intf; int /*<<< orphan*/  free_ioreqs; struct io_queue* free_ioreqs_buf; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending; int /*<<< orphan*/  processing; } ;
struct _adapter {struct io_queue* pio_queue; } ;
typedef  int addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NUM_IOREQ ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  kfree (struct io_queue*) ; 
 struct io_queue* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct io_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ register_intf_hdl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

uint r8712_alloc_io_queue(struct _adapter *adapter)
{
	u32 i;
	struct io_queue *pio_queue;
	struct io_req *pio_req;

	pio_queue = kmalloc(sizeof(*pio_queue), GFP_ATOMIC);
	if (!pio_queue)
		goto alloc_io_queue_fail;
	INIT_LIST_HEAD(&pio_queue->free_ioreqs);
	INIT_LIST_HEAD(&pio_queue->processing);
	INIT_LIST_HEAD(&pio_queue->pending);
	spin_lock_init(&pio_queue->lock);
	pio_queue->pallocated_free_ioreqs_buf = kzalloc(NUM_IOREQ *
						(sizeof(struct io_req)) + 4,
						GFP_ATOMIC);
	if ((pio_queue->pallocated_free_ioreqs_buf) == NULL)
		goto alloc_io_queue_fail;
	pio_queue->free_ioreqs_buf = pio_queue->pallocated_free_ioreqs_buf + 4
			- ((addr_t)(pio_queue->pallocated_free_ioreqs_buf)
			& 3);
	pio_req = (struct io_req *)(pio_queue->free_ioreqs_buf);
	for (i = 0; i < NUM_IOREQ; i++) {
		INIT_LIST_HEAD(&pio_req->list);
		list_add_tail(&pio_req->list, &pio_queue->free_ioreqs);
		pio_req++;
	}
	if ((register_intf_hdl((u8 *)adapter, &pio_queue->intf)) == _FAIL)
		goto alloc_io_queue_fail;
	adapter->pio_queue = pio_queue;
	return _SUCCESS;
alloc_io_queue_fail:
	if (pio_queue) {
		kfree(pio_queue->pallocated_free_ioreqs_buf);
		kfree(pio_queue);
	}
	adapter->pio_queue = NULL;
	return _FAIL;
}