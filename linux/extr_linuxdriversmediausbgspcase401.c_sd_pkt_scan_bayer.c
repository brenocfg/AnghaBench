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
struct cam {TYPE_1__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; int image_len; struct cam cam; } ;
struct TYPE_2__ {int sizeimage; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sd_complete_frame (struct gspca_dev*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sd_pkt_scan_bayer(struct gspca_dev *gspca_dev, u8 *data, int len)
{
	struct cam *cam = &gspca_dev->cam;
	int imagesize = cam->cam_mode[gspca_dev->curr_mode].sizeimage;

	if (gspca_dev->image_len == 0) {
		gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
		return;
	}

	if (gspca_dev->image_len + len >= imagesize) {
		sd_complete_frame(gspca_dev, data, len);
		return;
	}

	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}