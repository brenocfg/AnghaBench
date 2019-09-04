#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {scalar_t__ curr_mode; TYPE_2__ cam; } ;
typedef  int __u8 ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int* cx_inits_176 ; 
 int* cx_inits_320 ; 
 int* cx_inits_352 ; 
 int* cx_inits_640 ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int const*,int) ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void cx11646_initsize(struct gspca_dev *gspca_dev)
{
	const __u8 *cxinit;
	static const __u8 reg12[] = { 0x08, 0x05, 0x07, 0x04, 0x24 };
	static const __u8 reg17[] =
			{ 0x0a, 0x00, 0xf2, 0x01, 0x0f, 0x00, 0x97, 0x02 };

	switch (gspca_dev->cam.cam_mode[(int) gspca_dev->curr_mode].priv) {
	case 0:
		cxinit = cx_inits_640;
		break;
	case 1:
		cxinit = cx_inits_352;
		break;
	default:
/*	case 2: */
		cxinit = cx_inits_320;
		break;
	case 3:
		cxinit = cx_inits_176;
		break;
	}
	reg_w_val(gspca_dev, 0x009a, 0x01);
	reg_w_val(gspca_dev, 0x0010, 0x10);
	reg_w(gspca_dev, 0x0012, reg12, 5);
	reg_w(gspca_dev, 0x0017, reg17, 8);
	reg_w_val(gspca_dev, 0x00c0, 0x00);
	reg_w_val(gspca_dev, 0x00c1, 0x04);
	reg_w_val(gspca_dev, 0x00c2, 0x04);

	reg_w(gspca_dev, 0x0061, cxinit, 8);
	cxinit += 8;
	reg_w(gspca_dev, 0x00ca, cxinit, 8);
	cxinit += 8;
	reg_w(gspca_dev, 0x00d2, cxinit, 8);
	cxinit += 8;
	reg_w(gspca_dev, 0x00da, cxinit, 6);
	cxinit += 8;
	reg_w(gspca_dev, 0x0041, cxinit, 8);
	cxinit += 8;
	reg_w(gspca_dev, 0x0049, cxinit, 8);
	cxinit += 8;
	reg_w(gspca_dev, 0x0051, cxinit, 2);

	reg_r(gspca_dev, 0x0010, 1);
}