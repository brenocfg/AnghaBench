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
struct dvb_ringbuffer {size_t size; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; scalar_t__ error; void* data; scalar_t__ pwrite; scalar_t__ pread; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void dvb_ringbuffer_init(struct dvb_ringbuffer *rbuf, void *data, size_t len)
{
	rbuf->pread=rbuf->pwrite=0;
	rbuf->data=data;
	rbuf->size=len;
	rbuf->error=0;

	init_waitqueue_head(&rbuf->queue);

	spin_lock_init(&(rbuf->lock));
}