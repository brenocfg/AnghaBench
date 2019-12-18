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
struct sd {scalar_t__ bridge; int webcam; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_NW801 ; 
#define  Cvideopro 136 
#define  Dlink350c 135 
#define  DvcV6 134 
#define  Kr651us 133 
#define  Kritter 132 
#define  Proscope 131 
#define  SpaceCam 130 
#define  SpaceCam2 129 
#define  Twinkle 128 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 value;

	/* 'go' off */
	if (sd->bridge != BRIDGE_NW801) {
		value = 0x02;
		reg_w(gspca_dev, 0x0406, &value, 1);
	}

	/* LED off */
	switch (sd->webcam) {
	case Cvideopro:
	case Kr651us:
	case DvcV6:
	case Kritter:
		value = 0xff;
		break;
	case Dlink350c:
		value = 0x21;
		break;
	case SpaceCam:
	case SpaceCam2:
	case Proscope:
	case Twinkle:
		value = 0x01;
		break;
	default:
		return;
	}
	reg_w(gspca_dev, 0x0404, &value, 1);
}