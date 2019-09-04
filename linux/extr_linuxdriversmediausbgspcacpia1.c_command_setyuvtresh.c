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
struct TYPE_3__ {int /*<<< orphan*/  uvThreshold; int /*<<< orphan*/  yThreshold; } ;
struct TYPE_4__ {TYPE_1__ yuvThreshold; } ;
struct sd {TYPE_2__ params; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA_COMMAND_SetYUVThresh ; 
 int do_command (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int command_setyuvtresh(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	return do_command(gspca_dev, CPIA_COMMAND_SetYUVThresh,
			  sd->params.yuvThreshold.yThreshold,
			  sd->params.yuvThreshold.uvThreshold, 0, 0);
}