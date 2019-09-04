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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_ringbuffer {size_t pread; size_t size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  smp_store_release (size_t*,size_t) ; 

void dvb_ringbuffer_read(struct dvb_ringbuffer *rbuf, u8 *buf, size_t len)
{
	size_t todo = len;
	size_t split;

	split = (rbuf->pread + len > rbuf->size) ? rbuf->size - rbuf->pread : 0;
	if (split > 0) {
		memcpy(buf, rbuf->data+rbuf->pread, split);
		buf += split;
		todo -= split;
		/* smp_store_release() for read pointer update to ensure
		 * that buf is not overwritten until read is complete,
		 * this pairs with READ_ONCE() in dvb_ringbuffer_free()
		 */
		smp_store_release(&rbuf->pread, 0);
	}
	memcpy(buf, rbuf->data+rbuf->pread, todo);

	/* smp_store_release() to update read pointer, see above */
	smp_store_release(&rbuf->pread, (rbuf->pread + todo) % rbuf->size);
}