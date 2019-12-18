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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  which; int /*<<< orphan*/  pad; int /*<<< orphan*/  format; } ;
struct v4l2_subdev {int dummy; } ;
struct mt9v032 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * __mt9v032_get_pad_format (struct mt9v032*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mt9v032* to_mt9v032 (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v032_get_format(struct v4l2_subdev *subdev,
			      struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_format *format)
{
	struct mt9v032 *mt9v032 = to_mt9v032(subdev);

	format->format = *__mt9v032_get_pad_format(mt9v032, cfg, format->pad,
						   format->which);
	return 0;
}