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
typedef  int u16 ;
struct sd {int last_pts; int last_fid; } ;
struct TYPE_4__ {scalar_t__ pixelformat; int sizeimage; } ;
struct TYPE_3__ {scalar_t__ bulk; } ;
struct gspca_dev {scalar_t__ last_packet_type; int image_len; TYPE_2__ pixfmt; TYPE_1__ cam; } ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ DISCARD_PACKET ; 
 int /*<<< orphan*/  D_PACK ; 
 scalar_t__ FIRST_PACKET ; 
 scalar_t__ INTER_PACKET ; 
 scalar_t__ LAST_PACKET ; 
 int UVC_STREAM_EOF ; 
 int UVC_STREAM_ERR ; 
 int UVC_STREAM_FID ; 
 int UVC_STREAM_PTS ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,scalar_t__,int*,int) ; 
 int min (int,int) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data, int len)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u32 this_pts;
	u16 this_fid;
	int remaining_len = len;
	int payload_len;

	payload_len = gspca_dev->cam.bulk ? 2048 : 2040;
	do {
		len = min(remaining_len, payload_len);

		/* Payloads are prefixed with a UVC-style header.  We
		   consider a frame to start when the FID toggles, or the PTS
		   changes.  A frame ends when EOF is set, and we've received
		   the correct number of bytes. */

		/* Verify UVC header.  Header length is always 12 */
		if (data[0] != 12 || len < 12) {
			gspca_dbg(gspca_dev, D_PACK, "bad header\n");
			goto discard;
		}

		/* Check errors */
		if (data[1] & UVC_STREAM_ERR) {
			gspca_dbg(gspca_dev, D_PACK, "payload error\n");
			goto discard;
		}

		/* Extract PTS and FID */
		if (!(data[1] & UVC_STREAM_PTS)) {
			gspca_dbg(gspca_dev, D_PACK, "PTS not present\n");
			goto discard;
		}
		this_pts = (data[5] << 24) | (data[4] << 16)
						| (data[3] << 8) | data[2];
		this_fid = (data[1] & UVC_STREAM_FID) ? 1 : 0;

		/* If PTS or FID has changed, start a new frame. */
		if (this_pts != sd->last_pts || this_fid != sd->last_fid) {
			if (gspca_dev->last_packet_type == INTER_PACKET)
				gspca_frame_add(gspca_dev, LAST_PACKET,
						NULL, 0);
			sd->last_pts = this_pts;
			sd->last_fid = this_fid;
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					data + 12, len - 12);
		/* If this packet is marked as EOF, end the frame */
		} else if (data[1] & UVC_STREAM_EOF) {
			sd->last_pts = 0;
			if (gspca_dev->pixfmt.pixelformat != V4L2_PIX_FMT_JPEG
			 && gspca_dev->image_len + len - 12 !=
			    gspca_dev->pixfmt.sizeimage) {
				gspca_dbg(gspca_dev, D_PACK, "wrong sized frame\n");
				goto discard;
			}
			gspca_frame_add(gspca_dev, LAST_PACKET,
					data + 12, len - 12);
		} else {

			/* Add the data from this payload */
			gspca_frame_add(gspca_dev, INTER_PACKET,
					data + 12, len - 12);
		}

		/* Done this payload */
		goto scan_next;

discard:
		/* Discard data until a new frame starts. */
		gspca_dev->last_packet_type = DISCARD_PACKET;

scan_next:
		remaining_len -= len;
		data += len;
	} while (remaining_len > 0);
}