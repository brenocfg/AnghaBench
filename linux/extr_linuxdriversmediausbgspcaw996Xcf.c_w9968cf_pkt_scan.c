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
typedef  int u8 ;
struct sd {int* jpeg_hdr; } ;
struct gspca_dev {size_t curr_mode; scalar_t__ empty_packet; } ;
struct TYPE_2__ {scalar_t__ pixelformat; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int JPEG_HDR_SZ ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int*,int) ; 
 TYPE_1__* w9968cf_vga_mode ; 

__attribute__((used)) static void w9968cf_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (w9968cf_vga_mode[gspca_dev->curr_mode].pixelformat ==
	    V4L2_PIX_FMT_JPEG) {
		if (len >= 2 &&
		    data[0] == 0xff &&
		    data[1] == 0xd8) {
			gspca_frame_add(gspca_dev, LAST_PACKET,
					NULL, 0);
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					sd->jpeg_hdr, JPEG_HDR_SZ);
			/* Strip the ff d8, our own header (which adds
			   huffman and quantization tables) already has this */
			len -= 2;
			data += 2;
		}
	} else {
		/* In UYVY mode an empty packet signals EOF */
		if (gspca_dev->empty_packet) {
			gspca_frame_add(gspca_dev, LAST_PACKET,
						NULL, 0);
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					NULL, 0);
			gspca_dev->empty_packet = 0;
		}
	}
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}