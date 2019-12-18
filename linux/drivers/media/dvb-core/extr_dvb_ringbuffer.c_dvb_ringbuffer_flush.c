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
struct dvb_ringbuffer {scalar_t__ error; int /*<<< orphan*/  pwrite; int /*<<< orphan*/  pread; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dvb_ringbuffer_flush(struct dvb_ringbuffer *rbuf)
{
	/* dvb_ringbuffer_flush() counts as read operation
	 * smp_load_acquire() to load write pointer
	 * smp_store_release() to update read pointer, this ensures that the
	 * correct pointer is visible for subsequent dvb_ringbuffer_free()
	 * calls on other cpu cores
	 */
	smp_store_release(&rbuf->pread, smp_load_acquire(&rbuf->pwrite));
	rbuf->error = 0;
}