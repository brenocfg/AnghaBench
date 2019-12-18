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
struct sd {int pkt_seq; int const* jpeg_hdr; } ;
struct gspca_dev {scalar_t__ last_packet_type; } ;

/* Variables and functions */
 scalar_t__ DISCARD_PACKET ; 
 scalar_t__ FIRST_PACKET ; 
 int JPEG_HDR_SZ ; 
 scalar_t__ LAST_PACKET ; 
 int /*<<< orphan*/  add_packet (struct gspca_dev*,int*,int) ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,scalar_t__,int const*,int) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;
	static const u8 ffd9[] = {0xff, 0xd9};

	/* image packets start with:
	 *	02 8n
	 * with <n> bit:
	 *	0x01: even (0) / odd (1) image
	 *	0x02: end of image when set
	 */
	if (len < 3)
		return;				/* empty packet */
	if (*data == 0x02) {
		if (data[1] & 0x02) {
			sd->pkt_seq = !(data[1] & 1);
			add_packet(gspca_dev, data + 2, len - 2);
			gspca_frame_add(gspca_dev, LAST_PACKET,
					ffd9, 2);
			return;
		}
		if ((data[1] & 1) != sd->pkt_seq)
			goto err;
		if (gspca_dev->last_packet_type == LAST_PACKET)
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					sd->jpeg_hdr, JPEG_HDR_SZ);
		add_packet(gspca_dev, data + 2, len - 2);
		return;
	}
err:
	gspca_dev->last_packet_type = DISCARD_PACKET;
}