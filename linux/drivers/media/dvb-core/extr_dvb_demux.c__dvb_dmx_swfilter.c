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
struct dvb_demux {int tsbufp; int* tsbuf; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_swfilter_packet (struct dvb_demux*,int const*) ; 
 int find_next_packet (int const*,int,size_t,int const) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void _dvb_dmx_swfilter(struct dvb_demux *demux, const u8 *buf,
		size_t count, const int pktsize)
{
	int p = 0, i, j;
	const u8 *q;
	unsigned long flags;

	spin_lock_irqsave(&demux->lock, flags);

	if (demux->tsbufp) { /* tsbuf[0] is now 0x47. */
		i = demux->tsbufp;
		j = pktsize - i;
		if (count < j) {
			memcpy(&demux->tsbuf[i], buf, count);
			demux->tsbufp += count;
			goto bailout;
		}
		memcpy(&demux->tsbuf[i], buf, j);
		if (demux->tsbuf[0] == 0x47) /* double check */
			dvb_dmx_swfilter_packet(demux, demux->tsbuf);
		demux->tsbufp = 0;
		p += j;
	}

	while (1) {
		p = find_next_packet(buf, p, count, pktsize);
		if (p >= count)
			break;
		if (count - p < pktsize)
			break;

		q = &buf[p];

		if (pktsize == 204 && (*q == 0xB8)) {
			memcpy(demux->tsbuf, q, 188);
			demux->tsbuf[0] = 0x47;
			q = demux->tsbuf;
		}
		dvb_dmx_swfilter_packet(demux, q);
		p += pktsize;
	}

	i = count - p;
	if (i) {
		memcpy(demux->tsbuf, &buf[p], i);
		demux->tsbufp = i;
		if (pktsize == 204 && demux->tsbuf[0] == 0xB8)
			demux->tsbuf[0] = 0x47;
	}

bailout:
	spin_unlock_irqrestore(&demux->lock, flags);
}