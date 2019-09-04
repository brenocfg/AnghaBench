#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_mbus_code_enum {unsigned int index; int /*<<< orphan*/  code; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct soc_camera_host {TYPE_1__* ops; } ;
struct soc_camera_format_xlate {int dummy; } ;
struct soc_camera_device {unsigned int num_user_formats; TYPE_2__* user_formats; TYPE_2__* current_fmt; int /*<<< orphan*/  pdev; int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  code; scalar_t__ host_fmt; } ;
struct TYPE_6__ {int (* get_formats ) (struct soc_camera_device*,unsigned int,TYPE_2__*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  array_size (unsigned int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  enum_mbus_code ; 
 int /*<<< orphan*/  pad ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 scalar_t__ soc_mbus_get_fmtdesc (int /*<<< orphan*/ ) ; 
 int stub1 (struct soc_camera_device*,unsigned int,TYPE_2__*) ; 
 int stub2 (struct soc_camera_device*,unsigned int,TYPE_2__*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_mbus_code_enum*) ; 
 int /*<<< orphan*/  vfree (TYPE_2__*) ; 
 TYPE_2__* vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc_camera_init_user_formats(struct soc_camera_device *icd)
{
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	unsigned int i, fmts = 0, raw_fmts = 0;
	int ret;
	struct v4l2_subdev_mbus_code_enum code = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};

	while (!v4l2_subdev_call(sd, pad, enum_mbus_code, NULL, &code)) {
		raw_fmts++;
		code.index++;
	}

	if (!ici->ops->get_formats)
		/*
		 * Fallback mode - the host will have to serve all
		 * sensor-provided formats one-to-one to the user
		 */
		fmts = raw_fmts;
	else
		/*
		 * First pass - only count formats this host-sensor
		 * configuration can provide
		 */
		for (i = 0; i < raw_fmts; i++) {
			ret = ici->ops->get_formats(icd, i, NULL);
			if (ret < 0)
				return ret;
			fmts += ret;
		}

	if (!fmts)
		return -ENXIO;

	icd->user_formats =
		vmalloc(array_size(fmts,
				   sizeof(struct soc_camera_format_xlate)));
	if (!icd->user_formats)
		return -ENOMEM;

	dev_dbg(icd->pdev, "Found %d supported formats.\n", fmts);

	/* Second pass - actually fill data formats */
	fmts = 0;
	for (i = 0; i < raw_fmts; i++)
		if (!ici->ops->get_formats) {
			code.index = i;
			v4l2_subdev_call(sd, pad, enum_mbus_code, NULL, &code);
			icd->user_formats[fmts].host_fmt =
				soc_mbus_get_fmtdesc(code.code);
			if (icd->user_formats[fmts].host_fmt)
				icd->user_formats[fmts++].code = code.code;
		} else {
			ret = ici->ops->get_formats(icd, i,
						    &icd->user_formats[fmts]);
			if (ret < 0)
				goto egfmt;
			fmts += ret;
		}

	icd->num_user_formats = fmts;
	icd->current_fmt = &icd->user_formats[0];

	return 0;

egfmt:
	vfree(icd->user_formats);
	return ret;
}