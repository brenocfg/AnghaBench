#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sd {int restart_stream; int packet_read; int* packet; int pixels_read; } ;
struct TYPE_2__ {int width; int height; } ;
struct gspca_dev {scalar_t__ last_packet_type; TYPE_1__ pixfmt; } ;

/* Variables and functions */
 scalar_t__ DISCARD_PACKET ; 
 scalar_t__ FIRST_PACKET ; 
 scalar_t__ INTER_PACKET ; 
 scalar_t__ LAST_PACKET ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,scalar_t__,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  sd_complete_frame (struct gspca_dev*,int*,int) ; 

__attribute__((used)) static void sd_pkt_scan_janggu(struct gspca_dev *gspca_dev, u8 *data, int len)
{
	struct sd *sd = (struct sd *)gspca_dev;
	int imagesize = gspca_dev->pixfmt.width * gspca_dev->pixfmt.height;
	int i, plen, bits, pixels, info, count;

	if (sd->restart_stream)
		return;

	/* Sometimes a 1024 bytes garbage bulk packet is send between frames */
	if (gspca_dev->last_packet_type == LAST_PACKET && len == 1024) {
		gspca_dev->last_packet_type = DISCARD_PACKET;
		return;
	}

	i = 0;
	while (i < len) {
		/* Read header if not already be present from prev bulk pkt */
		if (sd->packet_read < 4) {
			count = 4 - sd->packet_read;
			if (count > len - i)
				count = len - i;
			memcpy(&sd->packet[sd->packet_read], &data[i], count);
			sd->packet_read += count;
			i += count;
			if (sd->packet_read < 4)
				break;
		}
		bits   = sd->packet[3] + (sd->packet[2] << 8);
		pixels = sd->packet[1] + ((sd->packet[0] & 0x3f) << 8);
		info   = (sd->packet[0] & 0xc0) >> 6;
		plen   = ((bits + 47) >> 4) << 1;
		/* Sanity checks */
		if (plen > 1024) {
			pr_err("invalid packet len %d restarting stream\n",
			       plen);
			goto error;
		}
		if (info == 3) {
			pr_err("unknown frame info value restarting stream\n");
			goto error;
		}

		/* Read (remainder of) packet contents */
		count = plen - sd->packet_read;
		if (count > len - i)
			count = len - i;
		memcpy(&sd->packet[sd->packet_read], &data[i], count);
		sd->packet_read += count;
		i += count;
		if (sd->packet_read < plen)
			break;

		sd->pixels_read += pixels;
		sd->packet_read = 0;

		switch (info) {
		case 0: /* Frame data */
			gspca_frame_add(gspca_dev, INTER_PACKET, sd->packet,
					plen);
			break;
		case 1: /* EOF */
			if (sd->pixels_read != imagesize) {
				pr_err("frame size %d expected %d\n",
				       sd->pixels_read, imagesize);
				goto error;
			}
			sd_complete_frame(gspca_dev, sd->packet, plen);
			return; /* Discard the rest of the bulk packet !! */
		case 2: /* SOF */
			gspca_frame_add(gspca_dev, FIRST_PACKET, sd->packet,
					plen);
			sd->pixels_read = pixels;
			break;
		}
	}
	return;

error:
	sd->restart_stream = 1;
	/* Give userspace a 0 bytes frame, so our dq callback gets
	   called and it can restart the stream */
	gspca_frame_add(gspca_dev, FIRST_PACKET, NULL, 0);
	gspca_frame_add(gspca_dev, LAST_PACKET, NULL, 0);
}