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
struct sd {int webcam; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
#define  Cvideopro 132 
#define  DvcV6 131 
#define  Kr651us 130 
#define  Kritter 129 
#define  P35u 128 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 v[2];

	switch (sd->webcam) {
	case P35u:
		v[0] = ((9 - val) << 3) | 0x01;
		reg_w(gspca_dev, 0x1019, v, 1);
		break;
	case Cvideopro:
	case DvcV6:
	case Kritter:
	case Kr651us:
		v[0] = val;
		v[1] = val >> 8;
		reg_w(gspca_dev, 0x101b, v, 2);
		break;
	}
}