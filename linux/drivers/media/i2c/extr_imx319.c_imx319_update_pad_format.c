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
struct TYPE_2__ {int /*<<< orphan*/  field; int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_format {TYPE_1__ format; } ;
struct imx319_mode {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct imx319 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  imx319_get_format_code (struct imx319*) ; 

__attribute__((used)) static void imx319_update_pad_format(struct imx319 *imx319,
				     const struct imx319_mode *mode,
				     struct v4l2_subdev_format *fmt)
{
	fmt->format.width = mode->width;
	fmt->format.height = mode->height;
	fmt->format.code = imx319_get_format_code(imx319);
	fmt->format.field = V4L2_FIELD_NONE;
}