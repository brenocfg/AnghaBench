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
struct sd {scalar_t__ bridge; int to_skip; } ;
struct TYPE_2__ {int width; } ;
struct gspca_dev {TYPE_1__ pixfmt; int /*<<< orphan*/  last_packet_type; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_ST6422 ; 
 int /*<<< orphan*/  DISCARD_PACKET ; 
 int /*<<< orphan*/  D_PACK ; 
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*) ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void stv06xx_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_PACK, "Packet of length %d arrived\n", len);

	/* A packet may contain several frames
	   loop until the whole packet is reached */
	while (len) {
		int id, chunk_len;

		if (len < 4) {
			gspca_dbg(gspca_dev, D_PACK, "Packet is smaller than 4 bytes\n");
			return;
		}

		/* Capture the id */
		id = (data[0] << 8) | data[1];

		/* Capture the chunk length */
		chunk_len = (data[2] << 8) | data[3];
		gspca_dbg(gspca_dev, D_PACK, "Chunk id: %x, length: %d\n",
			  id, chunk_len);

		data += 4;
		len -= 4;

		if (len < chunk_len) {
			gspca_err(gspca_dev, "URB packet length is smaller than the specified chunk length\n");
			gspca_dev->last_packet_type = DISCARD_PACKET;
			return;
		}

		/* First byte seem to be 02=data 2nd byte is unknown??? */
		if (sd->bridge == BRIDGE_ST6422 && (id & 0xff00) == 0x0200)
			goto frame_data;

		switch (id) {
		case 0x0200:
		case 0x4200:
frame_data:
			gspca_dbg(gspca_dev, D_PACK, "Frame data packet detected\n");

			if (sd->to_skip) {
				int skip = (sd->to_skip < chunk_len) ?
					    sd->to_skip : chunk_len;
				data += skip;
				len -= skip;
				chunk_len -= skip;
				sd->to_skip -= skip;
			}

			gspca_frame_add(gspca_dev, INTER_PACKET,
					data, chunk_len);
			break;

		case 0x8001:
		case 0x8005:
		case 0xc001:
		case 0xc005:
			gspca_dbg(gspca_dev, D_PACK, "Starting new frame\n");

			/* Create a new frame, chunk length should be zero */
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					NULL, 0);

			if (sd->bridge == BRIDGE_ST6422)
				sd->to_skip = gspca_dev->pixfmt.width * 4;

			if (chunk_len)
				gspca_err(gspca_dev, "Chunk length is non-zero on a SOF\n");
			break;

		case 0x8002:
		case 0x8006:
		case 0xc002:
			gspca_dbg(gspca_dev, D_PACK, "End of frame detected\n");

			/* Complete the last frame (if any) */
			gspca_frame_add(gspca_dev, LAST_PACKET,
					NULL, 0);

			if (chunk_len)
				gspca_err(gspca_dev, "Chunk length is non-zero on a EOF\n");
			break;

		case 0x0005:
			gspca_dbg(gspca_dev, D_PACK, "Chunk 0x005 detected\n");
			/* Unknown chunk with 11 bytes of data,
			   occurs just before end of each frame
			   in compressed mode */
			break;

		case 0x0100:
			gspca_dbg(gspca_dev, D_PACK, "Chunk 0x0100 detected\n");
			/* Unknown chunk with 2 bytes of data,
			   occurs 2-3 times per USB interrupt */
			break;
		case 0x42ff:
			gspca_dbg(gspca_dev, D_PACK, "Chunk 0x42ff detected\n");
			/* Special chunk seen sometimes on the ST6422 */
			break;
		default:
			gspca_dbg(gspca_dev, D_PACK, "Unknown chunk 0x%04x detected\n",
				  id);
			/* Unknown chunk */
		}
		data    += chunk_len;
		len     -= chunk_len;
	}
}