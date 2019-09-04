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
typedef  int u8 ;
struct sd {scalar_t__ sensor; TYPE_1__* saturation; } ;
struct gspca_dev {int dummy; } ;
typedef  int s16 ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 int const COLORS_DEF ; 
 scalar_t__ SENSOR_MI0360B ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 

__attribute__((used)) static void setcolors(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i, v, colors;
	const s16 *uv;
	u8 reg8a[12];			/* U & V gains */
	static const s16 uv_com[6] = {	/* same as reg84 in signed decimal */
		-24, -38, 64,		/* UR UG UB */
		 62, -51, -9		/* VR VG VB */
	};
	static const s16 uv_mi0360b[6] = {
		-20, -38, 64,		/* UR UG UB */
		 60, -51, -9		/* VR VG VB */
	};

	colors = sd->saturation->val;
	if (sd->sensor == SENSOR_MI0360B)
		uv = uv_mi0360b;
	else
		uv = uv_com;
	for (i = 0; i < 6; i++) {
		v = uv[i] * colors / COLORS_DEF;
		reg8a[i * 2] = v;
		reg8a[i * 2 + 1] = (v >> 8) & 0x0f;
	}
	reg_w(gspca_dev, 0x8a, reg8a, sizeof reg8a);
}