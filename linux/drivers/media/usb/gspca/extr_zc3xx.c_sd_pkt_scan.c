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
struct sd {int* jpeg_hdr; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int JPEG_HDR_SZ ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,
			int len)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* check the JPEG end of frame */
	if (len >= 3
	 && data[len - 3] == 0xff && data[len - 2] == 0xd9) {
/*fixme: what does the last byte mean?*/
		gspca_frame_add(gspca_dev, LAST_PACKET,
					data, len - 1);
		return;
	}

	/* check the JPEG start of a frame */
	if (data[0] == 0xff && data[1] == 0xd8) {
		/* put the JPEG header in the new frame */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
			sd->jpeg_hdr, JPEG_HDR_SZ);

		/* remove the webcam's header:
		 * ff d8 ff fe 00 0e 00 00 ss ss 00 01 ww ww hh hh pp pp
		 *	- 'ss ss' is the frame sequence number (BE)
		 *	- 'ww ww' and 'hh hh' are the window dimensions (BE)
		 *	- 'pp pp' is the packet sequence number (BE)
		 */
		data += 18;
		len -= 18;
	}
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}