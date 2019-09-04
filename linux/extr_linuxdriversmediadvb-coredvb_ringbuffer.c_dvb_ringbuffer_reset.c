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
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dvb_ringbuffer_reset(struct dvb_ringbuffer *rbuf)
{
	/* dvb_ringbuffer_reset() counts as read and write operation
	 * smp_store_release() to update read pointer
	 */
	smp_store_release(&rbuf->pread, 0);
	/* smp_store_release() to update write pointer */
	smp_store_release(&rbuf->pwrite, 0);
	rbuf->error = 0;
}