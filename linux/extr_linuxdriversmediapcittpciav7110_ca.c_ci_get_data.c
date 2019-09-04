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
struct dvb_ringbuffer {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_RINGBUFFER_WRITE_BYTE (struct dvb_ringbuffer*,int) ; 
 int dvb_ringbuffer_free (struct dvb_ringbuffer*) ; 
 int /*<<< orphan*/  dvb_ringbuffer_write (struct dvb_ringbuffer*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void ci_get_data(struct dvb_ringbuffer *cibuf, u8 *data, int len)
{
	if (dvb_ringbuffer_free(cibuf) < len + 2)
		return;

	DVB_RINGBUFFER_WRITE_BYTE(cibuf, len >> 8);
	DVB_RINGBUFFER_WRITE_BYTE(cibuf, len & 0xff);
	dvb_ringbuffer_write(cibuf, data, len);
	wake_up_interruptible(&cibuf->queue);
}