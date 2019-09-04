#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  cameraHeadID; int /*<<< orphan*/  vpRevision; int /*<<< orphan*/  vpVersion; } ;
struct TYPE_8__ {int /*<<< orphan*/  deviceRevision; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; } ;
struct TYPE_7__ {int /*<<< orphan*/  vcRevision; int /*<<< orphan*/  vcVersion; int /*<<< orphan*/  firmwareRevision; int /*<<< orphan*/  firmwareVersion; } ;
struct TYPE_6__ {scalar_t__ qx3_detected; } ;
struct TYPE_10__ {TYPE_4__ vpVersion; TYPE_3__ pnpID; TYPE_2__ version; TYPE_1__ qx3; } ;
struct sd {TYPE_5__ params; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  command_setlights (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int sd_start (struct gspca_dev*) ; 
 int /*<<< orphan*/  sd_stopN (struct gspca_dev*) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int ret;

	/* Start / Stop the camera to make sure we are talking to
	   a supported camera, and to get some information from it
	   to print. */
	ret = sd_start(gspca_dev);
	if (ret)
		return ret;

	/* Ensure the QX3 illuminators' states are restored upon resume,
	   or disable the illuminator controls, if this isn't a QX3 */
	if (sd->params.qx3.qx3_detected)
		command_setlights(gspca_dev);

	sd_stopN(gspca_dev);

	gspca_dbg(gspca_dev, D_PROBE, "CPIA Version:             %d.%02d (%d.%d)\n",
		  sd->params.version.firmwareVersion,
		  sd->params.version.firmwareRevision,
		  sd->params.version.vcVersion,
		  sd->params.version.vcRevision);
	gspca_dbg(gspca_dev, D_PROBE, "CPIA PnP-ID:              %04x:%04x:%04x",
		  sd->params.pnpID.vendor, sd->params.pnpID.product,
		  sd->params.pnpID.deviceRevision);
	gspca_dbg(gspca_dev, D_PROBE, "VP-Version:               %d.%d %04x",
		  sd->params.vpVersion.vpVersion,
		  sd->params.vpVersion.vpRevision,
		  sd->params.vpVersion.cameraHeadID);

	return 0;
}