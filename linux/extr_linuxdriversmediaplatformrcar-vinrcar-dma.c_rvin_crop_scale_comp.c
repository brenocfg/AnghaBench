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
struct TYPE_6__ {int field; scalar_t__ pixelformat; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {int left; int width; int top; int height; } ;
struct rvin_dev {TYPE_3__ format; TYPE_2__* info; TYPE_1__ crop; } ;
struct TYPE_5__ {scalar_t__ model; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ RCAR_GEN3 ; 
#define  V4L2_FIELD_INTERLACED 130 
#define  V4L2_FIELD_INTERLACED_BT 129 
#define  V4L2_FIELD_INTERLACED_TB 128 
 scalar_t__ V4L2_PIX_FMT_NV16 ; 
 int /*<<< orphan*/  VNELPRC_REG ; 
 int /*<<< orphan*/  VNEPPRC_REG ; 
 int /*<<< orphan*/  VNIS_REG ; 
 int /*<<< orphan*/  VNSLPRC_REG ; 
 int /*<<< orphan*/  VNSPPRC_REG ; 
 int /*<<< orphan*/  rvin_crop_scale_comp_gen2 (struct rvin_dev*) ; 
 int /*<<< orphan*/  rvin_write (struct rvin_dev*,int,int /*<<< orphan*/ ) ; 

void rvin_crop_scale_comp(struct rvin_dev *vin)
{
	/* Set Start/End Pixel/Line Pre-Clip */
	rvin_write(vin, vin->crop.left, VNSPPRC_REG);
	rvin_write(vin, vin->crop.left + vin->crop.width - 1, VNEPPRC_REG);

	switch (vin->format.field) {
	case V4L2_FIELD_INTERLACED:
	case V4L2_FIELD_INTERLACED_TB:
	case V4L2_FIELD_INTERLACED_BT:
		rvin_write(vin, vin->crop.top / 2, VNSLPRC_REG);
		rvin_write(vin, (vin->crop.top + vin->crop.height) / 2 - 1,
			   VNELPRC_REG);
		break;
	default:
		rvin_write(vin, vin->crop.top, VNSLPRC_REG);
		rvin_write(vin, vin->crop.top + vin->crop.height - 1,
			   VNELPRC_REG);
		break;
	}

	/* TODO: Add support for the UDS scaler. */
	if (vin->info->model != RCAR_GEN3)
		rvin_crop_scale_comp_gen2(vin);

	if (vin->format.pixelformat == V4L2_PIX_FMT_NV16)
		rvin_write(vin, ALIGN(vin->format.width, 0x20), VNIS_REG);
	else
		rvin_write(vin, ALIGN(vin->format.width, 0x10), VNIS_REG);
}