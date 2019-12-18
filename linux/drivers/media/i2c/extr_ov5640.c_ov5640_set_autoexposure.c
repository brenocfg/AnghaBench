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
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OV5640_REG_AEC_PK_MANUAL ; 
 int ov5640_mod_reg (struct ov5640_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov5640_set_autoexposure(struct ov5640_dev *sensor, bool on)
{
	return ov5640_mod_reg(sensor, OV5640_REG_AEC_PK_MANUAL,
			      BIT(0), on ? 0 : BIT(0));
}