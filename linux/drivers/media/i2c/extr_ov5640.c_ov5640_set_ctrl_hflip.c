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
struct ov5640_dev {int upside_down; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  OV5640_REG_TIMING_TC_REG21 ; 
 int ov5640_mod_reg (struct ov5640_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ov5640_set_ctrl_hflip(struct ov5640_dev *sensor, int value)
{
	/*
	 * If sensor is mounted upside down, mirror logic is inversed.
	 *
	 * Sensor is a BSI (Back Side Illuminated) one,
	 * so image captured is physically mirrored.
	 * This is why mirror logic is inversed in
	 * order to cancel this mirror effect.
	 */

	/*
	 * TIMING TC REG21:
	 * - [2]:	ISP mirror
	 * - [1]:	Sensor mirror
	 */
	return ov5640_mod_reg(sensor, OV5640_REG_TIMING_TC_REG21,
			      BIT(2) | BIT(1),
			      (!(value ^ sensor->upside_down)) ?
			      (BIT(2) | BIT(1)) : 0);
}