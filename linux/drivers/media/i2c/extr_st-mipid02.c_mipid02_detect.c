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
struct mipid02_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPID02_CLK_LANE_WR_REG1 ; 
 int mipid02_read_reg (struct mipid02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mipid02_detect(struct mipid02_dev *bridge)
{
	u8 reg;

	/*
	 * There is no version registers. Just try to read register
	 * MIPID02_CLK_LANE_WR_REG1.
	 */
	return mipid02_read_reg(bridge, MIPID02_CLK_LANE_WR_REG1, &reg);
}