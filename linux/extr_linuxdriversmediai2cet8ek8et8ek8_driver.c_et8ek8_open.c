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
struct v4l2_subdev_fh {int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct et8ek8_sensor {int dummy; } ;
struct et8ek8_reglist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET8EK8_REGLIST_MODE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 struct v4l2_mbus_framefmt* __et8ek8_get_pad_format (struct et8ek8_sensor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct et8ek8_reglist* et8ek8_reglist_find_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et8ek8_reglist_to_mbus (struct et8ek8_reglist*,struct v4l2_mbus_framefmt*) ; 
 int et8ek8_set_power (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  meta_reglist ; 
 struct et8ek8_sensor* to_et8ek8_sensor (struct v4l2_subdev*) ; 

__attribute__((used)) static int et8ek8_open(struct v4l2_subdev *sd, struct v4l2_subdev_fh *fh)
{
	struct et8ek8_sensor *sensor = to_et8ek8_sensor(sd);
	struct v4l2_mbus_framefmt *format;
	struct et8ek8_reglist *reglist;

	reglist = et8ek8_reglist_find_type(&meta_reglist, ET8EK8_REGLIST_MODE);
	format = __et8ek8_get_pad_format(sensor, fh->pad, 0,
					 V4L2_SUBDEV_FORMAT_TRY);
	et8ek8_reglist_to_mbus(reglist, format);

	return et8ek8_set_power(sd, true);
}