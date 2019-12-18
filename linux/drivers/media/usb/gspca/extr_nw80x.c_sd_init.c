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
struct sd {int bridge; int /*<<< orphan*/  webcam; } ;
struct gspca_dev {int usb_err; } ;

/* Variables and functions */
#define  BRIDGE_NW800 132 
#define  Mustek300 131 
#define  P35u 130 
#define  Proscope 129 
#define  SpaceCam 128 
 int /*<<< orphan*/  nw800_init ; 
 int /*<<< orphan*/  proscope_init ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spacecam_init ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->bridge) {
	case BRIDGE_NW800:
		switch (sd->webcam) {
		case SpaceCam:
			reg_w_buf(gspca_dev, spacecam_init);
			break;
		default:
			reg_w_buf(gspca_dev, nw800_init);
			break;
		}
		break;
	default:
		switch (sd->webcam) {
		case Mustek300:
		case P35u:
		case Proscope:
			reg_w_buf(gspca_dev, proscope_init);
			break;
		}
		break;
	}
	return gspca_dev->usb_err;
}