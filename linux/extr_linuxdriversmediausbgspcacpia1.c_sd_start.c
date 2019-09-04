#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int colStart; int rowStart; int colEnd; int rowEnd; } ;
struct TYPE_13__ {int /*<<< orphan*/  videoSize; } ;
struct TYPE_10__ {scalar_t__ systemState; int /*<<< orphan*/  vpStatus; scalar_t__ fatalError; } ;
struct TYPE_9__ {scalar_t__ firmwareVersion; } ;
struct TYPE_16__ {int streamStartLine; TYPE_6__ roi; TYPE_5__ format; TYPE_2__ status; TYPE_1__ version; } ;
struct sd {int first_frame; int /*<<< orphan*/  fps; int /*<<< orphan*/  cam_exposure; scalar_t__ exposure_count; int /*<<< orphan*/  exposure_status; TYPE_8__ params; } ;
struct TYPE_15__ {int width; int height; } ;
struct TYPE_12__ {TYPE_3__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; TYPE_7__ pixfmt; TYPE_4__ cam; } ;
struct TYPE_11__ {int priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA_COMMAND_DiscardFrame ; 
 int /*<<< orphan*/  CPIA_COMMAND_GetCameraStatus ; 
 int /*<<< orphan*/  CPIA_COMMAND_GetVPVersion ; 
 int /*<<< orphan*/  CPIA_COMMAND_ModifyCameraStatus ; 
 int /*<<< orphan*/  CPIA_COMMAND_SetCompression ; 
 int /*<<< orphan*/  CPIA_COMMAND_SetGrabMode ; 
 int /*<<< orphan*/  CPIA_COMPRESSION_NONE ; 
 int /*<<< orphan*/  CPIA_GRAB_CONTINEOUS ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  EXPOSURE_NORMAL ; 
 int /*<<< orphan*/  NO_DECIMATION ; 
 int /*<<< orphan*/  STREAMSTATE ; 
 int /*<<< orphan*/  STREAM_NOT_READY ; 
 int /*<<< orphan*/  VIDEOSIZE_CIF ; 
 int /*<<< orphan*/  VIDEOSIZE_QCIF ; 
 scalar_t__ WARM_BOOT_STATE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int command_resume (struct gspca_dev*) ; 
 int command_setapcor (struct gspca_dev*) ; 
 int command_setcolourbalance (struct gspca_dev*) ; 
 int command_setcolourparams (struct gspca_dev*) ; 
 int command_setcompressionparams (struct gspca_dev*) ; 
 int command_setcompressiontarget (struct gspca_dev*) ; 
 int command_setecptiming (struct gspca_dev*) ; 
 int command_setexposure (struct gspca_dev*) ; 
 int command_setflickerctrl (struct gspca_dev*) ; 
 int command_setformat (struct gspca_dev*) ; 
 int command_setsensorfps (struct gspca_dev*) ; 
 int command_setvloffset (struct gspca_dev*) ; 
 int command_setyuvtresh (struct gspca_dev*) ; 
 int do_command (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_version_information (struct gspca_dev*) ; 
 int goto_high_power (struct gspca_dev*) ; 
 int goto_low_power (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  printstatus (struct gspca_dev*,TYPE_8__*) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int priv, ret;

	/* Start the camera in low power mode */
	if (goto_low_power(gspca_dev)) {
		if (sd->params.status.systemState != WARM_BOOT_STATE) {
			gspca_err(gspca_dev, "unexpected systemstate: %02x\n",
				  sd->params.status.systemState);
			printstatus(gspca_dev, &sd->params);
			return -ENODEV;
		}

		/* FIXME: this is just dirty trial and error */
		ret = goto_high_power(gspca_dev);
		if (ret)
			return ret;

		ret = do_command(gspca_dev, CPIA_COMMAND_DiscardFrame,
				 0, 0, 0, 0);
		if (ret)
			return ret;

		ret = goto_low_power(gspca_dev);
		if (ret)
			return ret;
	}

	/* procedure described in developer's guide p3-28 */

	/* Check the firmware version. */
	sd->params.version.firmwareVersion = 0;
	get_version_information(gspca_dev);

	/* The fatal error checking should be done after
	 * the camera powers up (developer's guide p 3-38) */

	/* Set streamState before transition to high power to avoid bug
	 * in firmware 1-02 */
	ret = do_command(gspca_dev, CPIA_COMMAND_ModifyCameraStatus,
			 STREAMSTATE, 0, STREAM_NOT_READY, 0);
	if (ret)
		return ret;

	/* GotoHiPower */
	ret = goto_high_power(gspca_dev);
	if (ret)
		return ret;

	/* Check the camera status */
	ret = do_command(gspca_dev, CPIA_COMMAND_GetCameraStatus, 0, 0, 0, 0);
	if (ret)
		return ret;

	if (sd->params.status.fatalError) {
		gspca_err(gspca_dev, "fatal_error: %04x, vp_status: %04x\n",
			  sd->params.status.fatalError,
			  sd->params.status.vpStatus);
		return -EIO;
	}

	/* VPVersion can't be retrieved before the camera is in HiPower,
	 * so get it here instead of in get_version_information. */
	ret = do_command(gspca_dev, CPIA_COMMAND_GetVPVersion, 0, 0, 0, 0);
	if (ret)
		return ret;

	/* Determine video mode settings */
	sd->params.streamStartLine = 120;

	priv = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	if (priv & 0x01) { /* crop */
		sd->params.roi.colStart = 2;
		sd->params.roi.rowStart = 6;
	} else {
		sd->params.roi.colStart = 0;
		sd->params.roi.rowStart = 0;
	}

	if (priv & 0x02) { /* quarter */
		sd->params.format.videoSize = VIDEOSIZE_QCIF;
		sd->params.roi.colStart /= 2;
		sd->params.roi.rowStart /= 2;
		sd->params.streamStartLine /= 2;
	} else
		sd->params.format.videoSize = VIDEOSIZE_CIF;

	sd->params.roi.colEnd = sd->params.roi.colStart +
				(gspca_dev->pixfmt.width >> 3);
	sd->params.roi.rowEnd = sd->params.roi.rowStart +
				(gspca_dev->pixfmt.height >> 2);

	/* And now set the camera to a known state */
	ret = do_command(gspca_dev, CPIA_COMMAND_SetGrabMode,
			 CPIA_GRAB_CONTINEOUS, 0, 0, 0);
	if (ret)
		return ret;
	/* We start with compression disabled, as we need one uncompressed
	   frame to handle later compressed frames */
	ret = do_command(gspca_dev, CPIA_COMMAND_SetCompression,
			 CPIA_COMPRESSION_NONE,
			 NO_DECIMATION, 0, 0);
	if (ret)
		return ret;
	ret = command_setcompressiontarget(gspca_dev);
	if (ret)
		return ret;
	ret = command_setcolourparams(gspca_dev);
	if (ret)
		return ret;
	ret = command_setformat(gspca_dev);
	if (ret)
		return ret;
	ret = command_setyuvtresh(gspca_dev);
	if (ret)
		return ret;
	ret = command_setecptiming(gspca_dev);
	if (ret)
		return ret;
	ret = command_setcompressionparams(gspca_dev);
	if (ret)
		return ret;
	ret = command_setexposure(gspca_dev);
	if (ret)
		return ret;
	ret = command_setcolourbalance(gspca_dev);
	if (ret)
		return ret;
	ret = command_setsensorfps(gspca_dev);
	if (ret)
		return ret;
	ret = command_setapcor(gspca_dev);
	if (ret)
		return ret;
	ret = command_setflickerctrl(gspca_dev);
	if (ret)
		return ret;
	ret = command_setvloffset(gspca_dev);
	if (ret)
		return ret;

	/* Start stream */
	ret = command_resume(gspca_dev);
	if (ret)
		return ret;

	/* Wait 6 frames before turning compression on for the sensor to get
	   all settings and AEC/ACB to settle */
	sd->first_frame = 6;
	sd->exposure_status = EXPOSURE_NORMAL;
	sd->exposure_count = 0;
	atomic_set(&sd->cam_exposure, 0);
	atomic_set(&sd->fps, 0);

	return 0;
}