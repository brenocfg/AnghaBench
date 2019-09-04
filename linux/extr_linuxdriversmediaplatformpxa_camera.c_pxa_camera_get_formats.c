#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_subdev_mbus_code_enum {unsigned int index; int code; int /*<<< orphan*/  which; } ;
struct v4l2_device {int dummy; } ;
struct pxa_mbus_pixelfmt {int /*<<< orphan*/  name; int /*<<< orphan*/  bits_per_sample; } ;
struct pxa_camera_format_xlate {int code; struct pxa_mbus_pixelfmt const* host_fmt; } ;
struct pxa_camera_dev {int dummy; } ;

/* Variables and functions */
#define  MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE 133 
#define  MEDIA_BUS_FMT_RGB565_2X8_LE 132 
#define  MEDIA_BUS_FMT_UYVY8_2X8 131 
#define  MEDIA_BUS_FMT_VYUY8_2X8 130 
#define  MEDIA_BUS_FMT_YUYV8_2X8 129 
#define  MEDIA_BUS_FMT_YVYU8_2X8 128 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  enum_mbus_code ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  pcdev_to_dev (struct pxa_camera_dev*) ; 
 struct pxa_mbus_pixelfmt const* pxa_camera_formats ; 
 int /*<<< orphan*/  pxa_camera_packing_supported (struct pxa_mbus_pixelfmt const*) ; 
 int pxa_camera_try_bus_param (struct pxa_camera_dev*,int /*<<< orphan*/ ) ; 
 struct pxa_mbus_pixelfmt* pxa_mbus_get_fmtdesc (int) ; 
 int sensor_call (struct pxa_camera_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_mbus_code_enum*) ; 
 struct pxa_camera_dev* v4l2_dev_to_pcdev (struct v4l2_device*) ; 

__attribute__((used)) static int pxa_camera_get_formats(struct v4l2_device *v4l2_dev,
				  unsigned int idx,
				  struct pxa_camera_format_xlate *xlate)
{
	struct pxa_camera_dev *pcdev = v4l2_dev_to_pcdev(v4l2_dev);
	int formats = 0, ret;
	struct v4l2_subdev_mbus_code_enum code = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.index = idx,
	};
	const struct pxa_mbus_pixelfmt *fmt;

	ret = sensor_call(pcdev, pad, enum_mbus_code, NULL, &code);
	if (ret < 0)
		/* No more formats */
		return 0;

	fmt = pxa_mbus_get_fmtdesc(code.code);
	if (!fmt) {
		dev_err(pcdev_to_dev(pcdev),
			"Invalid format code #%u: %d\n", idx, code.code);
		return 0;
	}

	/* This also checks support for the requested bits-per-sample */
	ret = pxa_camera_try_bus_param(pcdev, fmt->bits_per_sample);
	if (ret < 0)
		return 0;

	switch (code.code) {
	case MEDIA_BUS_FMT_UYVY8_2X8:
		formats++;
		if (xlate) {
			xlate->host_fmt	= &pxa_camera_formats[0];
			xlate->code	= code.code;
			xlate++;
			dev_dbg(pcdev_to_dev(pcdev),
				"Providing format %s using code %d\n",
				pxa_camera_formats[0].name, code.code);
		}
	/* fall through */
	case MEDIA_BUS_FMT_VYUY8_2X8:
	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_YVYU8_2X8:
	case MEDIA_BUS_FMT_RGB565_2X8_LE:
	case MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE:
		if (xlate)
			dev_dbg(pcdev_to_dev(pcdev),
				"Providing format %s packed\n",
				fmt->name);
		break;
	default:
		if (!pxa_camera_packing_supported(fmt))
			return 0;
		if (xlate)
			dev_dbg(pcdev_to_dev(pcdev),
				"Providing format %s in pass-through mode\n",
				fmt->name);
		break;
	}

	/* Generic pass-through */
	formats++;
	if (xlate) {
		xlate->host_fmt	= fmt;
		xlate->code	= code.code;
		xlate++;
	}

	return formats;
}