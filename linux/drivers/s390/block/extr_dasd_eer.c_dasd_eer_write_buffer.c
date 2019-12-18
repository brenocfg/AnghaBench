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
struct eerbuffer {unsigned long head; unsigned long buffersize; scalar_t__* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 

__attribute__((used)) static void dasd_eer_write_buffer(struct eerbuffer *eerb,
				  char *data, int count)
{

	unsigned long headindex,localhead;
	unsigned long rest, len;
	char *nextdata;

	nextdata = data;
	rest = count;
	while (rest > 0) {
 		headindex = eerb->head / PAGE_SIZE;
 		localhead = eerb->head % PAGE_SIZE;
		len = min(rest, PAGE_SIZE - localhead);
		memcpy(eerb->buffer[headindex]+localhead, nextdata, len);
		nextdata += len;
		rest -= len;
		eerb->head += len;
		if (eerb->head == eerb->buffersize)
			eerb->head = 0; /* wrap around */
		BUG_ON(eerb->head > eerb->buffersize);
	}
}