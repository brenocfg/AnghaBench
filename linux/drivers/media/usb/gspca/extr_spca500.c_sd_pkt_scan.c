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
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int JPEG_HDR_SZ ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 scalar_t__ SPCA500_OFFSET_DATA ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i;
	static __u8 ffd9[] = {0xff, 0xd9};

/* frames are jpeg 4.1.1 without 0xff escape */
	if (data[0] == 0xff) {
		if (data[1] != 0x01) {	/* drop packet */
/*			gspca_dev->last_packet_type = DISCARD_PACKET; */
			return;
		}
		gspca_frame_add(gspca_dev, LAST_PACKET,
					ffd9, 2);

		/* put the JPEG header in the new frame */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
			sd->jpeg_hdr, JPEG_HDR_SZ);

		data += SPCA500_OFFSET_DATA;
		len -= SPCA500_OFFSET_DATA;
	} else {
		data += 1;
		len -= 1;
	}

	/* add 0x00 after 0xff */
	i = 0;
	do {
		if (data[i] == 0xff) {
			gspca_frame_add(gspca_dev, INTER_PACKET,
					data, i + 1);
			len -= i;
			data += i;
			*data = 0x00;
			i = 0;
		}
		i++;
	} while (i < len);
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}