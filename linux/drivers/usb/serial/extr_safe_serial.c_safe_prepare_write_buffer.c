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
struct usb_serial_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  write_fifo; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CRC10_INITFCS ; 
 int fcs_compute10 (unsigned char*,int,int /*<<< orphan*/ ) ; 
 int kfifo_out_locked (int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ padded ; 
 scalar_t__ safe ; 

__attribute__((used)) static int safe_prepare_write_buffer(struct usb_serial_port *port,
						void *dest, size_t size)
{
	unsigned char *buf = dest;
	int count;
	int trailer_len;
	int pkt_len;
	__u16 fcs;

	trailer_len = safe ? 2 : 0;

	count = kfifo_out_locked(&port->write_fifo, buf, size - trailer_len,
								&port->lock);
	if (!safe)
		return count;

	/* pad if necessary */
	if (padded) {
		pkt_len = size;
		memset(buf + count, '0', pkt_len - count - trailer_len);
	} else {
		pkt_len = count + trailer_len;
	}

	/* set count */
	buf[pkt_len - 2] = count << 2;
	buf[pkt_len - 1] = 0;

	/* compute fcs and insert into trailer */
	fcs = fcs_compute10(buf, pkt_len, CRC10_INITFCS);
	buf[pkt_len - 2] |= fcs >> 8;
	buf[pkt_len - 1] |= fcs & 0xff;

	return pkt_len;
}