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
struct sd {scalar_t__ bridge; int quality; int* jpeg_hdr; } ;
struct gspca_dev {void* last_packet_type; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_TP6810 ; 
 void* DISCARD_PACKET ; 
 int /*<<< orphan*/  D_FRAM ; 
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int JPEG_HDR_SZ ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  set_dqt (struct gspca_dev*,int) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,
			int len)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* the start of frame contains:
	 *	ff d8
	 *	ff fe
	 *	width / 16
	 *	height / 8
	 *	quality
	 */
	if (sd->bridge == BRIDGE_TP6810) {
		if (*data != 0x5a) {
/*fixme: don't discard the whole frame..*/
			if (*data == 0xaa || *data == 0x00)
				return;
			if (*data > 0xc0) {
				gspca_dbg(gspca_dev, D_FRAM, "bad frame\n");
				gspca_dev->last_packet_type = DISCARD_PACKET;
				return;
			}
		}
		data++;
		len--;
		if (len < 2) {
			gspca_dev->last_packet_type = DISCARD_PACKET;
			return;
		}
		if (*data == 0xff && data[1] == 0xd8) {
/*fixme: there may be information in the 4 high bits*/
			if (len < 7) {
				gspca_dev->last_packet_type = DISCARD_PACKET;
				return;
			}
			if ((data[6] & 0x0f) != sd->quality)
				set_dqt(gspca_dev, data[6] & 0x0f);
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					sd->jpeg_hdr, JPEG_HDR_SZ);
			gspca_frame_add(gspca_dev, INTER_PACKET,
					data + 7, len - 7);
		} else if (data[len - 2] == 0xff && data[len - 1] == 0xd9) {
			gspca_frame_add(gspca_dev, LAST_PACKET,
					data, len);
		} else {
			gspca_frame_add(gspca_dev, INTER_PACKET,
					data, len);
		}
		return;
	}

	switch (*data) {
	case 0x55:
		gspca_frame_add(gspca_dev, LAST_PACKET, data, 0);

		if (len < 8
		 || data[1] != 0xff || data[2] != 0xd8
		 || data[3] != 0xff || data[4] != 0xfe) {

			/* Have only seen this with corrupt frames */
			gspca_dev->last_packet_type = DISCARD_PACKET;
			return;
		}
		if (data[7] != sd->quality)
			set_dqt(gspca_dev, data[7]);
		gspca_frame_add(gspca_dev, FIRST_PACKET,
				sd->jpeg_hdr, JPEG_HDR_SZ);
		gspca_frame_add(gspca_dev, INTER_PACKET,
				data + 8, len - 8);
		break;
	case 0xaa:
		gspca_dev->last_packet_type = DISCARD_PACKET;
		break;
	case 0xcc:
		if (len >= 3 && (data[1] != 0xff || data[2] != 0xd8))
			gspca_frame_add(gspca_dev, INTER_PACKET,
					data + 1, len - 1);
		else
			gspca_dev->last_packet_type = DISCARD_PACKET;
		break;
	}
}