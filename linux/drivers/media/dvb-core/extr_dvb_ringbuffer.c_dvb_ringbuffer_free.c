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
struct dvb_ringbuffer {scalar_t__ pwrite; scalar_t__ size; int /*<<< orphan*/  pread; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 

ssize_t dvb_ringbuffer_free(struct dvb_ringbuffer *rbuf)
{
	ssize_t free;

	/* READ_ONCE() to load read pointer on writer side
	 * this pairs with smp_store_release() in dvb_ringbuffer_read(),
	 * dvb_ringbuffer_read_user(), dvb_ringbuffer_flush(),
	 * or dvb_ringbuffer_reset()
	 */
	free = READ_ONCE(rbuf->pread) - rbuf->pwrite;
	if (free <= 0)
		free += rbuf->size;
	return free-1;
}