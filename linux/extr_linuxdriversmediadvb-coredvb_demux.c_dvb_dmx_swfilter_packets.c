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
typedef  int u8 ;
struct dvb_demux {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_swfilter_packet (struct dvb_demux*,int const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void dvb_dmx_swfilter_packets(struct dvb_demux *demux, const u8 *buf,
			      size_t count)
{
	unsigned long flags;

	spin_lock_irqsave(&demux->lock, flags);

	while (count--) {
		if (buf[0] == 0x47)
			dvb_dmx_swfilter_packet(demux, buf);
		buf += 188;
	}

	spin_unlock_irqrestore(&demux->lock, flags);
}