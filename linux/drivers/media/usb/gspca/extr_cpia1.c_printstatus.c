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
struct gspca_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  errorCode; int /*<<< orphan*/  vpStatus; int /*<<< orphan*/  debugFlags; int /*<<< orphan*/  cmdError; int /*<<< orphan*/  fatalError; int /*<<< orphan*/  streamState; int /*<<< orphan*/  grabState; int /*<<< orphan*/  systemState; } ;
struct cam_params {TYPE_1__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void printstatus(struct gspca_dev *gspca_dev, struct cam_params *params)
{
	gspca_dbg(gspca_dev, D_PROBE, "status: %02x %02x %02x %02x %02x %02x %02x %02x\n",
		  params->status.systemState, params->status.grabState,
		  params->status.streamState, params->status.fatalError,
		  params->status.cmdError, params->status.debugFlags,
		  params->status.vpStatus, params->status.errorCode);
}