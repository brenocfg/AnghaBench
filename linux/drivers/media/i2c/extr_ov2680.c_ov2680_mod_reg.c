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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ov2680_dev {int dummy; } ;

/* Variables and functions */
 int ov2680_read_reg (struct ov2680_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ov2680_write_reg (struct ov2680_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov2680_mod_reg(struct ov2680_dev *sensor, u16 reg, u8 mask, u8 val)
{
	u32 readval;
	int ret;

	ret = ov2680_read_reg(sensor, reg, &readval);
	if (ret < 0)
		return ret;

	readval &= ~mask;
	val &= mask;
	val |= readval;

	return ov2680_write_reg(sensor, reg, val);
}