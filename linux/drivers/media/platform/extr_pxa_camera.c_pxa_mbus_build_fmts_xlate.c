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
struct v4l2_subdev_mbus_code_enum {int /*<<< orphan*/  index; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_device {int dummy; } ;
struct pxa_camera_format_xlate {scalar_t__ code; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 struct pxa_camera_format_xlate* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_mbus_code ; 
 struct pxa_camera_format_xlate* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pxa_camera_format_xlate*) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_mbus_code_enum*) ; 

__attribute__((used)) static struct pxa_camera_format_xlate *pxa_mbus_build_fmts_xlate(
	struct v4l2_device *v4l2_dev, struct v4l2_subdev *subdev,
	int (*get_formats)(struct v4l2_device *, unsigned int,
			   struct pxa_camera_format_xlate *xlate))
{
	unsigned int i, fmts = 0, raw_fmts = 0;
	int ret;
	struct v4l2_subdev_mbus_code_enum code = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	struct pxa_camera_format_xlate *user_formats;

	while (!v4l2_subdev_call(subdev, pad, enum_mbus_code, NULL, &code)) {
		raw_fmts++;
		code.index++;
	}

	/*
	 * First pass - only count formats this host-sensor
	 * configuration can provide
	 */
	for (i = 0; i < raw_fmts; i++) {
		ret = get_formats(v4l2_dev, i, NULL);
		if (ret < 0)
			return ERR_PTR(ret);
		fmts += ret;
	}

	if (!fmts)
		return ERR_PTR(-ENXIO);

	user_formats = kcalloc(fmts + 1, sizeof(*user_formats), GFP_KERNEL);
	if (!user_formats)
		return ERR_PTR(-ENOMEM);

	/* Second pass - actually fill data formats */
	fmts = 0;
	for (i = 0; i < raw_fmts; i++) {
		ret = get_formats(v4l2_dev, i, user_formats + fmts);
		if (ret < 0)
			goto egfmt;
		fmts += ret;
	}
	user_formats[fmts].code = 0;

	return user_formats;
egfmt:
	kfree(user_formats);
	return ERR_PTR(ret);
}