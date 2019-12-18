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
struct sd {size_t sensor; } ;
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; TYPE_2__ cam; } ;
struct cap_s {int cc_sizeid; int /*<<< orphan*/  cc_bytes; } ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int SQ930_CTRL_CAP_START ; 
 struct cap_s** capconfig ; 
 int /*<<< orphan*/  reg_wb (struct gspca_dev*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void send_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	const struct cap_s *cap;
	int mode;

	mode = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	cap = &capconfig[sd->sensor][mode];
	reg_wb(gspca_dev, 0x0900 | SQ930_CTRL_CAP_START,
			0x0a00 | cap->cc_sizeid,
			cap->cc_bytes, 32);
}