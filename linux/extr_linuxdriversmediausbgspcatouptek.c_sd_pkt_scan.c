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
struct sd {scalar_t__ this_f; } ;
struct TYPE_2__ {scalar_t__ sizeimage; } ;
struct gspca_dev {TYPE_1__ pixfmt; } ;

/* Variables and functions */
 int BULK_SIZE ; 
 int /*<<< orphan*/  DISCARD_PACKET ; 
 int /*<<< orphan*/  D_FRAM ; 
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,	/* isoc packet */
			int len)	/* iso packet length */
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (len != BULK_SIZE) {
		/* can we finish a frame? */
		if (sd->this_f + len == gspca_dev->pixfmt.sizeimage) {
			gspca_frame_add(gspca_dev, LAST_PACKET, data, len);
			gspca_dbg(gspca_dev, D_FRAM, "finish frame sz %u/%u w/ len %u\n\n",
				  sd->this_f, gspca_dev->pixfmt.sizeimage, len);
		/* lost some data, discard the frame */
		} else {
			gspca_frame_add(gspca_dev, DISCARD_PACKET, NULL, 0);
			gspca_dbg(gspca_dev, D_FRAM, "abort frame sz %u/%u w/ len %u\n\n",
				  sd->this_f, gspca_dev->pixfmt.sizeimage, len);
		}
		sd->this_f = 0;
	} else {
		if (sd->this_f == 0)
			gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
		else
			gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
		sd->this_f += len;
	}
}