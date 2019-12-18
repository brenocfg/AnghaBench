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
typedef  scalar_t__ u8 ;
struct sd {scalar_t__ sensor; scalar_t__ frame_rate; } ;
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; TYPE_2__ cam; } ;
struct TYPE_3__ {scalar_t__ priv; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rate_s const*) ; 
 int /*<<< orphan*/  D_PROBE ; 
 scalar_t__ SENSOR_OV772x ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ov534_reg_write (struct gspca_dev*,int,scalar_t__) ; 
 int /*<<< orphan*/  sccb_reg_write (struct gspca_dev*,int,scalar_t__) ; 

__attribute__((used)) static void set_frame_rate(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i;
	struct rate_s {
		u8 fps;
		u8 r11;
		u8 r0d;
		u8 re5;
	};
	const struct rate_s *r;
	static const struct rate_s rate_0[] = {	/* 640x480 */
		{60, 0x01, 0xc1, 0x04},
		{50, 0x01, 0x41, 0x02},
		{40, 0x02, 0xc1, 0x04},
		{30, 0x04, 0x81, 0x02},
		{15, 0x03, 0x41, 0x04},
	};
	static const struct rate_s rate_1[] = {	/* 320x240 */
/*		{205, 0x01, 0xc1, 0x02},  * 205 FPS: video is partly corrupt */
		{187, 0x01, 0x81, 0x02}, /* 187 FPS or below: video is valid */
		{150, 0x01, 0xc1, 0x04},
		{137, 0x02, 0xc1, 0x02},
		{125, 0x02, 0x81, 0x02},
		{100, 0x02, 0xc1, 0x04},
		{75, 0x03, 0xc1, 0x04},
		{60, 0x04, 0xc1, 0x04},
		{50, 0x02, 0x41, 0x04},
		{37, 0x03, 0x41, 0x04},
		{30, 0x04, 0x41, 0x04},
	};

	if (sd->sensor != SENSOR_OV772x)
		return;
	if (gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv == 0) {
		r = rate_0;
		i = ARRAY_SIZE(rate_0);
	} else {
		r = rate_1;
		i = ARRAY_SIZE(rate_1);
	}
	while (--i > 0) {
		if (sd->frame_rate >= r->fps)
			break;
		r++;
	}

	sccb_reg_write(gspca_dev, 0x11, r->r11);
	sccb_reg_write(gspca_dev, 0x0d, r->r0d);
	ov534_reg_write(gspca_dev, 0xe5, r->re5);

	gspca_dbg(gspca_dev, D_PROBE, "frame_rate: %d\n", r->fps);
}