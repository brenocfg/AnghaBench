#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sd {int npkt; int pktsz; int short_mark; int* jpeg_hdr; int nchg; int quality; scalar_t__ ag_cnt; int /*<<< orphan*/  work; } ;
struct gspca_dev {scalar_t__ last_packet_type; TYPE_2__** urb; } ;
struct TYPE_4__ {TYPE_1__* iso_frame_desc; } ;
struct TYPE_3__ {int length; } ;

/* Variables and functions */
 void* DISCARD_PACKET ; 
 scalar_t__ FIRST_PACKET ; 
 scalar_t__ INTER_PACKET ; 
 int JPEG_HDR_SZ ; 
 scalar_t__ LAST_PACKET ; 
 int QUALITY_MAX ; 
 int QUALITY_MIN ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,scalar_t__,int*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_lum (struct sd*,int*) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i, new_qual;

	/*
	 * A frame ends on the marker
	 *		ff ff 00 c4 c4 96 ..
	 * which is 62 bytes long and is followed by various information
	 * including statuses and luminosity.
	 *
	 * A marker may be split on two packets.
	 *
	 * The 6th byte of a marker contains the bits:
	 *	0x08: USB full
	 *	0xc0: frame sequence
	 * When the bit 'USB full' is set, the frame must be discarded;
	 * this is also the case when the 2 bytes before the marker are
	 * not the JPEG end of frame ('ff d9').
	 */

	/* count the packets and their size */
	sd->npkt++;
	sd->pktsz += len;

/*fixme: assumption about the following code:
 *	- there can be only one marker in a packet
 */

	/* skip the remaining bytes of a short marker */
	i = sd->short_mark;
	if (i != 0) {
		sd->short_mark = 0;
		if (i < 0	/* if 'ff' at end of previous packet */
		 && data[0] == 0xff
		 && data[1] == 0x00)
			goto marker_found;
		if (data[0] == 0xff && data[1] == 0xff) {
			i = 0;
			goto marker_found;
		}
		len -= i;
		if (len <= 0)
			return;
		data += i;
	}

	/* search backwards if there is a marker in the packet */
	for (i = len - 1; --i >= 0; ) {
		if (data[i] != 0xff) {
			i--;
			continue;
		}
		if (data[i + 1] == 0xff) {

			/* (there may be 'ff ff' inside a marker) */
			if (i + 2 >= len || data[i + 2] == 0x00)
				goto marker_found;
		}
	}

	/* no marker found */
	/* add the JPEG header if first fragment */
	if (data[len - 1] == 0xff)
		sd->short_mark = -1;
	if (gspca_dev->last_packet_type == LAST_PACKET)
		gspca_frame_add(gspca_dev, FIRST_PACKET,
				sd->jpeg_hdr, JPEG_HDR_SZ);
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
	return;

	/* marker found */
	/* if some error, discard the frame and decrease the quality */
marker_found:
	new_qual = 0;
	if (i > 2) {
		if (data[i - 2] != 0xff || data[i - 1] != 0xd9) {
			gspca_dev->last_packet_type = DISCARD_PACKET;
			new_qual = -3;
		}
	} else if (i + 6 < len) {
		if (data[i + 6] & 0x08) {
			gspca_dev->last_packet_type = DISCARD_PACKET;
			new_qual = -5;
		}
	}

	gspca_frame_add(gspca_dev, LAST_PACKET, data, i);

	/* compute the filling rate and a new JPEG quality */
	if (new_qual == 0) {
		int r;

		r = (sd->pktsz * 100) /
			(sd->npkt *
				gspca_dev->urb[0]->iso_frame_desc[0].length);
		if (r >= 85)
			new_qual = -3;
		else if (r < 75)
			new_qual = 2;
	}
	if (new_qual != 0) {
		sd->nchg += new_qual;
		if (sd->nchg < -6 || sd->nchg >= 12) {
			sd->nchg = 0;
			new_qual += sd->quality;
			if (new_qual < QUALITY_MIN)
				new_qual = QUALITY_MIN;
			else if (new_qual > QUALITY_MAX)
				new_qual = QUALITY_MAX;
			if (new_qual != sd->quality) {
				sd->quality = new_qual;
				schedule_work(&sd->work);
			}
		}
	} else {
		sd->nchg = 0;
	}
	sd->pktsz = sd->npkt = 0;

	/* if the marker is smaller than 62 bytes,
	 * memorize the number of bytes to skip in the next packet */
	if (i + 62 > len) {			/* no more usable data */
		sd->short_mark = i + 62 - len;
		return;
	}
	if (sd->ag_cnt >= 0)
		set_lum(sd, data + i);

	/* if more data, start a new frame */
	i += 62;
	if (i < len) {
		data += i;
		len -= i;
		gspca_frame_add(gspca_dev, FIRST_PACKET,
				sd->jpeg_hdr, JPEG_HDR_SZ);
		gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
	}
}