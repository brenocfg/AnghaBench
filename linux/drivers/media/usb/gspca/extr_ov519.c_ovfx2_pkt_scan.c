#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int width; int height; } ;
struct TYPE_5__ {TYPE_1__ pixfmt; } ;
struct sd {TYPE_2__ gspca_dev; scalar_t__ first_frame; } ;
struct TYPE_6__ {int bulk_size; } ;
struct gspca_dev {int image_len; int /*<<< orphan*/  last_packet_type; TYPE_3__ cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCARD_PACKET ; 
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ovfx2_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;

	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);

	/* A short read signals EOF */
	if (len < gspca_dev->cam.bulk_size) {
		/* If the frame is short, and it is one of the first ones
		   the sensor and bridge are still syncing, so drop it. */
		if (sd->first_frame) {
			sd->first_frame--;
			if (gspca_dev->image_len <
				  sd->gspca_dev.pixfmt.width *
					sd->gspca_dev.pixfmt.height)
				gspca_dev->last_packet_type = DISCARD_PACKET;
		}
		gspca_frame_add(gspca_dev, LAST_PACKET, NULL, 0);
		gspca_frame_add(gspca_dev, FIRST_PACKET, NULL, 0);
	}
}