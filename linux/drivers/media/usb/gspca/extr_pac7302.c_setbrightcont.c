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
typedef  int u8 ;
struct sd {TYPE_2__* contrast; TYPE_1__* brightness; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;
struct TYPE_4__ {int const val; scalar_t__ maximum; } ;
struct TYPE_3__ {int val; scalar_t__ maximum; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setbrightcont(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i, v;
	static const u8 max[10] =
		{0x29, 0x33, 0x42, 0x5a, 0x6e, 0x80, 0x9f, 0xbb,
		 0xd4, 0xec};
	static const u8 delta[10] =
		{0x35, 0x33, 0x33, 0x2f, 0x2a, 0x25, 0x1e, 0x17,
		 0x11, 0x0b};

	reg_w(gspca_dev, 0xff, 0x00);		/* page 0 */
	for (i = 0; i < 10; i++) {
		v = max[i];
		v += (sd->brightness->val - (s32)sd->brightness->maximum)
			* 150 / (s32)sd->brightness->maximum; /* 200 ? */
		v -= delta[i] * sd->contrast->val / (s32)sd->contrast->maximum;
		if (v < 0)
			v = 0;
		else if (v > 0xff)
			v = 0xff;
		reg_w(gspca_dev, 0xa2 + i, v);
	}
	reg_w(gspca_dev, 0xdc, 0x01);
}