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
struct TYPE_2__ {int sizeimage; } ;
struct sd {TYPE_1__ mode; } ;
struct gspca_dev {int /*<<< orphan*/  last_packet_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCARD_PACKET ; 
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,
			int len)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* Every now and then the camera sends a 16 byte packet, no idea
	   what it contains, but it is not image data, when this
	   happens the frame received before this packet is corrupt,
	   so discard it. */
	if (len != sd->mode.sizeimage) {
		gspca_dev->last_packet_type = DISCARD_PACKET;
		return;
	}

	/* Finish the previous frame, we do this upon reception of the next
	   packet, even though it is already complete so that the strange 16
	   byte packets send after a corrupt frame can discard it. */
	gspca_frame_add(gspca_dev, LAST_PACKET, NULL, 0);

	/* Store the just received frame */
	gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
}