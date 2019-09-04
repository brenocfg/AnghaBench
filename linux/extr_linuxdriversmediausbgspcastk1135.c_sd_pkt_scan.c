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
struct stk1135_pkt_header {int flags; int seq; int /*<<< orphan*/  gpio; } ;
struct sd {int flip_status; int pkt_seq; scalar_t__ flip_debounce; } ;
struct gspca_dev {int /*<<< orphan*/  last_packet_type; } ;
typedef  enum gspca_packet_type { ____Placeholder_gspca_packet_type } gspca_packet_type ;

/* Variables and functions */
 int /*<<< orphan*/  DISCARD_PACKET ; 
 int /*<<< orphan*/  D_PACK ; 
 int FIRST_PACKET ; 
 int INTER_PACKET ; 
 int LAST_PACKET ; 
 int STK1135_HDR_FRAME_START ; 
 int STK1135_HDR_SEQ_MASK ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int,int*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;
	int skip = sizeof(struct stk1135_pkt_header);
	bool flip;
	enum gspca_packet_type pkt_type = INTER_PACKET;
	struct stk1135_pkt_header *hdr = (void *)data;
	u8 seq;

	if (len < 4) {
		gspca_dbg(gspca_dev, D_PACK, "received short packet (less than 4 bytes)\n");
		return;
	}

	/* GPIO 8 is flip sensor (1 = normal position, 0 = flipped to back) */
	flip = !(le16_to_cpu(hdr->gpio) & (1 << 8));
	/* it's a switch, needs software debounce */
	if (sd->flip_status != flip)
		sd->flip_debounce++;
	else
		sd->flip_debounce = 0;

	/* check sequence number (not present in new frame packets) */
	if (!(hdr->flags & STK1135_HDR_FRAME_START)) {
		seq = hdr->seq & STK1135_HDR_SEQ_MASK;
		if (seq != sd->pkt_seq) {
			gspca_dbg(gspca_dev, D_PACK, "received out-of-sequence packet\n");
			/* resync sequence and discard packet */
			sd->pkt_seq = seq;
			gspca_dev->last_packet_type = DISCARD_PACKET;
			return;
		}
	}
	sd->pkt_seq++;
	if (sd->pkt_seq > STK1135_HDR_SEQ_MASK)
		sd->pkt_seq = 0;

	if (len == sizeof(struct stk1135_pkt_header))
		return;

	if (hdr->flags & STK1135_HDR_FRAME_START) { /* new frame */
		skip = 8;	/* the header is longer */
		gspca_frame_add(gspca_dev, LAST_PACKET, data, 0);
		pkt_type = FIRST_PACKET;
	}
	gspca_frame_add(gspca_dev, pkt_type, data + skip, len - skip);
}