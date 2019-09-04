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
struct dvb_ringbuffer {scalar_t__ pread; scalar_t__ size; int /*<<< orphan*/  pwrite; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ smp_load_acquire (int /*<<< orphan*/ *) ; 

ssize_t dvb_ringbuffer_avail(struct dvb_ringbuffer *rbuf)
{
	ssize_t avail;

	/* smp_load_acquire() to load write pointer on reader side
	 * this pairs with smp_store_release() in dvb_ringbuffer_write(),
	 * dvb_ringbuffer_write_user(), or dvb_ringbuffer_reset()
	 */
	avail = smp_load_acquire(&rbuf->pwrite) - rbuf->pread;
	if (avail < 0)
		avail += rbuf->size;
	return avail;
}