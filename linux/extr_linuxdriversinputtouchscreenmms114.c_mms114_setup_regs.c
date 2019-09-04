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
struct touchscreen_properties {int max_x; int max_y; } ;
struct mms114_data {scalar_t__ type; int contact_threshold; int moving_threshold; struct touchscreen_properties props; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMS114_CONTACT_THRESHOLD ; 
 int /*<<< orphan*/  MMS114_MOVING_THRESHOLD ; 
 int /*<<< orphan*/  MMS114_XY_RESOLUTION_H ; 
 int /*<<< orphan*/  MMS114_X_RESOLUTION ; 
 int /*<<< orphan*/  MMS114_Y_RESOLUTION ; 
 scalar_t__ TYPE_MMS152 ; 
 int mms114_get_version (struct mms114_data*) ; 
 int mms114_set_active (struct mms114_data*,int) ; 
 int mms114_write_reg (struct mms114_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mms114_setup_regs(struct mms114_data *data)
{
	const struct touchscreen_properties *props = &data->props;
	int val;
	int error;

	error = mms114_get_version(data);
	if (error < 0)
		return error;

	/* MMS152 has no configuration or power on registers */
	if (data->type == TYPE_MMS152)
		return 0;

	error = mms114_set_active(data, true);
	if (error < 0)
		return error;

	val = (props->max_x >> 8) & 0xf;
	val |= ((props->max_y >> 8) & 0xf) << 4;
	error = mms114_write_reg(data, MMS114_XY_RESOLUTION_H, val);
	if (error < 0)
		return error;

	val = props->max_x & 0xff;
	error = mms114_write_reg(data, MMS114_X_RESOLUTION, val);
	if (error < 0)
		return error;

	val = props->max_x & 0xff;
	error = mms114_write_reg(data, MMS114_Y_RESOLUTION, val);
	if (error < 0)
		return error;

	if (data->contact_threshold) {
		error = mms114_write_reg(data, MMS114_CONTACT_THRESHOLD,
				data->contact_threshold);
		if (error < 0)
			return error;
	}

	if (data->moving_threshold) {
		error = mms114_write_reg(data, MMS114_MOVING_THRESHOLD,
				data->moving_threshold);
		if (error < 0)
			return error;
	}

	return 0;
}