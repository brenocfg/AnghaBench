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
typedef  int u8 ;
struct fc2580_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int fc2580_wr_reg_ff(struct fc2580_dev *dev, u8 reg, u8 val)
{
	if (val == 0xff)
		return 0;
	else
		return regmap_write(dev->regmap, reg, val);
}