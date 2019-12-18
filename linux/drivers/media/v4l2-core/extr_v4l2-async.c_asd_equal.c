#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  address; int /*<<< orphan*/  adapter_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  fwnode; TYPE_1__ i2c; int /*<<< orphan*/  device_name; } ;
struct v4l2_async_subdev {int match_type; TYPE_2__ match; } ;

/* Variables and functions */
#define  V4L2_ASYNC_MATCH_DEVNAME 130 
#define  V4L2_ASYNC_MATCH_FWNODE 129 
#define  V4L2_ASYNC_MATCH_I2C 128 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool asd_equal(struct v4l2_async_subdev *asd_x,
		      struct v4l2_async_subdev *asd_y)
{
	if (asd_x->match_type != asd_y->match_type)
		return false;

	switch (asd_x->match_type) {
	case V4L2_ASYNC_MATCH_DEVNAME:
		return strcmp(asd_x->match.device_name,
			      asd_y->match.device_name) == 0;
	case V4L2_ASYNC_MATCH_I2C:
		return asd_x->match.i2c.adapter_id ==
			asd_y->match.i2c.adapter_id &&
			asd_x->match.i2c.address ==
			asd_y->match.i2c.address;
	case V4L2_ASYNC_MATCH_FWNODE:
		return asd_x->match.fwnode == asd_y->match.fwnode;
	default:
		break;
	}

	return false;
}