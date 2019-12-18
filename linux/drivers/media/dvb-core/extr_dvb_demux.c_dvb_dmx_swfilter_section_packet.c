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
struct dvb_demux_feed {int cc; int pusi_seen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_BUFFER_FLAG_DISCONTINUITY_DETECTED ; 
 int /*<<< orphan*/  DMX_BUFFER_FLAG_DISCONTINUITY_INDICATOR ; 
 int /*<<< orphan*/  dprintk_sect_loss (char*,int,...) ; 
 int /*<<< orphan*/  dvb_dmx_swfilter_section_copy_dump (struct dvb_demux_feed*,int const*,int) ; 
 int /*<<< orphan*/  dvb_dmx_swfilter_section_new (struct dvb_demux_feed*) ; 
 int payload (int const*) ; 
 int /*<<< orphan*/  set_buf_flags (struct dvb_demux_feed*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvb_dmx_swfilter_section_packet(struct dvb_demux_feed *feed,
					   const u8 *buf)
{
	u8 p, count;
	int ccok, dc_i = 0;
	u8 cc;

	count = payload(buf);

	if (count == 0)		/* count == 0 if no payload or out of range */
		return -1;

	p = 188 - count;	/* payload start */

	cc = buf[3] & 0x0f;
	ccok = ((feed->cc + 1) & 0x0f) == cc;
	feed->cc = cc;

	if (buf[3] & 0x20) {
		/* adaption field present, check for discontinuity_indicator */
		if ((buf[4] > 0) && (buf[5] & 0x80))
			dc_i = 1;
	}

	if (!ccok || dc_i) {
		if (dc_i) {
			set_buf_flags(feed,
				      DMX_BUFFER_FLAG_DISCONTINUITY_INDICATOR);
			dprintk_sect_loss("%d frame with disconnect indicator\n",
				cc);
		} else {
			set_buf_flags(feed,
				      DMX_BUFFER_FLAG_DISCONTINUITY_DETECTED);
			dprintk_sect_loss("discontinuity: %d instead of %d. %d bytes lost\n",
				cc, (feed->cc + 1) & 0x0f, count + 4);
		}
		/*
		 * those bytes under some circumstances will again be reported
		 * in the following dvb_dmx_swfilter_section_new
		 */

		/*
		 * Discontinuity detected. Reset pusi_seen to
		 * stop feeding of suspicious data until next PUSI=1 arrives
		 *
		 * FIXME: does it make sense if the MPEG-TS is the one
		 *	reporting discontinuity?
		 */

		feed->pusi_seen = false;
		dvb_dmx_swfilter_section_new(feed);
	}

	if (buf[1] & 0x40) {
		/* PUSI=1 (is set), section boundary is here */
		if (count > 1 && buf[p] < count) {
			const u8 *before = &buf[p + 1];
			u8 before_len = buf[p];
			const u8 *after = &before[before_len];
			u8 after_len = count - 1 - before_len;

			dvb_dmx_swfilter_section_copy_dump(feed, before,
							   before_len);
			/* before start of new section, set pusi_seen */
			feed->pusi_seen = true;
			dvb_dmx_swfilter_section_new(feed);
			dvb_dmx_swfilter_section_copy_dump(feed, after,
							   after_len);
		} else if (count > 0) {
			set_buf_flags(feed,
				      DMX_BUFFER_FLAG_DISCONTINUITY_DETECTED);
			dprintk_sect_loss("PUSI=1 but %d bytes lost\n", count);
		}
	} else {
		/* PUSI=0 (is not set), no section boundary */
		dvb_dmx_swfilter_section_copy_dump(feed, &buf[p], count);
	}

	return 0;
}