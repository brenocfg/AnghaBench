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
struct TYPE_3__ {int /*<<< orphan*/  decimationThreshMod; int /*<<< orphan*/  qDiffStepThresh; int /*<<< orphan*/  frDiffStepThresh; int /*<<< orphan*/  decimationHysteresis; int /*<<< orphan*/  largeStep; int /*<<< orphan*/  smallStep; int /*<<< orphan*/  threshMax; int /*<<< orphan*/  hysteresis; } ;
struct TYPE_4__ {TYPE_1__ compressionParams; } ;
struct sd {TYPE_2__ params; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA_COMMAND_SetCompressionParams ; 
 int do_command_extended (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int command_setcompressionparams(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	return do_command_extended(gspca_dev,
			    CPIA_COMMAND_SetCompressionParams,
			    0, 0, 0, 0,
			    sd->params.compressionParams.hysteresis,
			    sd->params.compressionParams.threshMax,
			    sd->params.compressionParams.smallStep,
			    sd->params.compressionParams.largeStep,
			    sd->params.compressionParams.decimationHysteresis,
			    sd->params.compressionParams.frDiffStepThresh,
			    sd->params.compressionParams.qDiffStepThresh,
			    sd->params.compressionParams.decimationThreshMod);
}