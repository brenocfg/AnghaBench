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
struct TYPE_3__ {scalar_t__ systemState; } ;
struct TYPE_4__ {TYPE_1__ status; } ;
struct sd {TYPE_2__ params; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA_COMMAND_GetCameraStatus ; 
 int /*<<< orphan*/  CPIA_COMMAND_GotoHiPower ; 
 int /*<<< orphan*/  D_CONF ; 
 int EINTR ; 
 int EIO ; 
 scalar_t__ HI_POWER_STATE ; 
 int /*<<< orphan*/  current ; 
 int do_command (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*,scalar_t__) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  printstatus (struct gspca_dev*,TYPE_2__*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goto_high_power(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int ret;

	ret = do_command(gspca_dev, CPIA_COMMAND_GotoHiPower, 0, 0, 0, 0);
	if (ret)
		return ret;

	msleep_interruptible(40);	/* windows driver does it too */

	if (signal_pending(current))
		return -EINTR;

	ret = do_command(gspca_dev, CPIA_COMMAND_GetCameraStatus, 0, 0, 0, 0);
	if (ret)
		return ret;

	if (sd->params.status.systemState != HI_POWER_STATE) {
		gspca_err(gspca_dev, "unexpected state after hi power cmd: %02x\n",
			  sd->params.status.systemState);
		printstatus(gspca_dev, &sd->params);
		return -EIO;
	}

	gspca_dbg(gspca_dev, D_CONF, "camera now in HIGH power state\n");
	return 0;
}