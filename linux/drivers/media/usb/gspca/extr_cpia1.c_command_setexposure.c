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
struct TYPE_3__ {int expMode; int /*<<< orphan*/  coarseExpHi; int /*<<< orphan*/  coarseExpLo; int /*<<< orphan*/  fineExp; int /*<<< orphan*/  gain; int /*<<< orphan*/  blueComp; int /*<<< orphan*/  green2Comp; int /*<<< orphan*/  green1Comp; int /*<<< orphan*/  redComp; int /*<<< orphan*/  centreWeight; int /*<<< orphan*/  compMode; int /*<<< orphan*/  gainMode; } ;
struct TYPE_4__ {TYPE_1__ exposure; } ;
struct sd {TYPE_2__ params; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA_COMMAND_SetExposure ; 
 int do_command_extended (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int command_setexposure(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int ret;

	ret = do_command_extended(gspca_dev, CPIA_COMMAND_SetExposure,
				  sd->params.exposure.gainMode,
				  1,
				  sd->params.exposure.compMode,
				  sd->params.exposure.centreWeight,
				  sd->params.exposure.gain,
				  sd->params.exposure.fineExp,
				  sd->params.exposure.coarseExpLo,
				  sd->params.exposure.coarseExpHi,
				  sd->params.exposure.redComp,
				  sd->params.exposure.green1Comp,
				  sd->params.exposure.green2Comp,
				  sd->params.exposure.blueComp);
	if (ret)
		return ret;

	if (sd->params.exposure.expMode != 1) {
		ret = do_command_extended(gspca_dev, CPIA_COMMAND_SetExposure,
					  0,
					  sd->params.exposure.expMode,
					  0, 0,
					  sd->params.exposure.gain,
					  sd->params.exposure.fineExp,
					  sd->params.exposure.coarseExpLo,
					  sd->params.exposure.coarseExpHi,
					  0, 0, 0, 0);
	}

	return ret;
}