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
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (data[0] == 0xff && data[1] == 0xd8) {

		/* start of frame */
		gspca_frame_add(gspca_dev, LAST_PACKET, NULL, 0);

		/* put the JPEG header in the new frame */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
				sd->jpeg_hdr, JPEG_HDR_SZ);
		data += 2;
		len -= 2;
	}
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}