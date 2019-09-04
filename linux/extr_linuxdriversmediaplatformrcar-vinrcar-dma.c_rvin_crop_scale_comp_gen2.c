#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int field; int height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {int height; int width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_4__ {int height; int width; } ;
struct rvin_dev {TYPE_3__ format; TYPE_2__ crop; TYPE_1__ compose; } ;

/* Variables and functions */
#define  V4L2_FIELD_INTERLACED 130 
#define  V4L2_FIELD_INTERLACED_BT 129 
#define  V4L2_FIELD_INTERLACED_TB 128 
 int /*<<< orphan*/  VNELPOC_REG ; 
 int /*<<< orphan*/  VNEPPOC_REG ; 
 int /*<<< orphan*/  VNSLPOC_REG ; 
 int /*<<< orphan*/  VNSPPOC_REG ; 
 int /*<<< orphan*/  VNXS_REG ; 
 int /*<<< orphan*/  VNYS_REG ; 
 int /*<<< orphan*/  rvin_set_coeff (struct rvin_dev*,int) ; 
 int /*<<< orphan*/  rvin_write (struct rvin_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vin_dbg (struct rvin_dev*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rvin_crop_scale_comp_gen2(struct rvin_dev *vin)
{
	u32 xs, ys;

	/* Set scaling coefficient */
	ys = 0;
	if (vin->crop.height != vin->compose.height)
		ys = (4096 * vin->crop.height) / vin->compose.height;
	rvin_write(vin, ys, VNYS_REG);

	xs = 0;
	if (vin->crop.width != vin->compose.width)
		xs = (4096 * vin->crop.width) / vin->compose.width;

	/* Horizontal upscaling is up to double size */
	if (xs > 0 && xs < 2048)
		xs = 2048;

	rvin_write(vin, xs, VNXS_REG);

	/* Horizontal upscaling is done out by scaling down from double size */
	if (xs < 4096)
		xs *= 2;

	rvin_set_coeff(vin, xs);

	/* Set Start/End Pixel/Line Post-Clip */
	rvin_write(vin, 0, VNSPPOC_REG);
	rvin_write(vin, 0, VNSLPOC_REG);
	rvin_write(vin, vin->format.width - 1, VNEPPOC_REG);
	switch (vin->format.field) {
	case V4L2_FIELD_INTERLACED:
	case V4L2_FIELD_INTERLACED_TB:
	case V4L2_FIELD_INTERLACED_BT:
		rvin_write(vin, vin->format.height / 2 - 1, VNELPOC_REG);
		break;
	default:
		rvin_write(vin, vin->format.height - 1, VNELPOC_REG);
		break;
	}

	vin_dbg(vin,
		"Pre-Clip: %ux%u@%u:%u YS: %d XS: %d Post-Clip: %ux%u@%u:%u\n",
		vin->crop.width, vin->crop.height, vin->crop.left,
		vin->crop.top, ys, xs, vin->format.width, vin->format.height,
		0, 0);
}