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
typedef  int /*<<< orphan*/  u8 ;
struct solo_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_I2C_TW ; 
 int /*<<< orphan*/  TW_CHIP_OFFSET_ADDR (int) ; 
 scalar_t__ is_tw286x (struct solo_dev*,int) ; 
 int /*<<< orphan*/  solo_i2c_readbyte (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 tw_readbyte(struct solo_dev *solo_dev, int chip_id, u8 tw6x_off,
		      u8 tw_off)
{
	if (is_tw286x(solo_dev, chip_id))
		return solo_i2c_readbyte(solo_dev, SOLO_I2C_TW,
					 TW_CHIP_OFFSET_ADDR(chip_id),
					 tw6x_off);
	else
		return solo_i2c_readbyte(solo_dev, SOLO_I2C_TW,
					 TW_CHIP_OFFSET_ADDR(chip_id),
					 tw_off);
}