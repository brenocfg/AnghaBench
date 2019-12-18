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
struct ov5640_mode_info {int /*<<< orphan*/  reg_data; } ;
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ov5640_load_regs (struct ov5640_dev*,struct ov5640_mode_info const*) ; 

__attribute__((used)) static int ov5640_set_mode_direct(struct ov5640_dev *sensor,
				  const struct ov5640_mode_info *mode)
{
	if (!mode->reg_data)
		return -EINVAL;

	/* Write capture setting */
	return ov5640_load_regs(sensor, mode);
}