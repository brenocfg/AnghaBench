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
struct v4l2_subdev_frame_size_enum {unsigned int index; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  code; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_4__ {struct v4l2_subdev* source; } ;
struct stm32_dcmi {unsigned int num_of_sd_framesizes; int /*<<< orphan*/  dev; TYPE_3__* sd_framesizes; TYPE_2__* sd_format; TYPE_1__ entity; } ;
struct dcmi_framesize {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enum_frame_size ; 
 int /*<<< orphan*/  pad ; 
 unsigned int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_size_enum*) ; 

__attribute__((used)) static int dcmi_framesizes_init(struct stm32_dcmi *dcmi)
{
	unsigned int num_fsize = 0;
	struct v4l2_subdev *subdev = dcmi->entity.source;
	struct v4l2_subdev_frame_size_enum fse = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.code = dcmi->sd_format->mbus_code,
	};
	unsigned int ret;
	unsigned int i;

	/* Allocate discrete framesizes array */
	while (!v4l2_subdev_call(subdev, pad, enum_frame_size,
				 NULL, &fse))
		fse.index++;

	num_fsize = fse.index;
	if (!num_fsize)
		return 0;

	dcmi->num_of_sd_framesizes = num_fsize;
	dcmi->sd_framesizes = devm_kcalloc(dcmi->dev, num_fsize,
					   sizeof(struct dcmi_framesize),
					   GFP_KERNEL);
	if (!dcmi->sd_framesizes) {
		dev_err(dcmi->dev, "Could not allocate memory\n");
		return -ENOMEM;
	}

	/* Fill array with sensor supported framesizes */
	dev_dbg(dcmi->dev, "Sensor supports %u frame sizes:\n", num_fsize);
	for (i = 0; i < dcmi->num_of_sd_framesizes; i++) {
		fse.index = i;
		ret = v4l2_subdev_call(subdev, pad, enum_frame_size,
				       NULL, &fse);
		if (ret)
			return ret;
		dcmi->sd_framesizes[fse.index].width = fse.max_width;
		dcmi->sd_framesizes[fse.index].height = fse.max_height;
		dev_dbg(dcmi->dev, "%ux%u\n", fse.max_width, fse.max_height);
	}

	return 0;
}