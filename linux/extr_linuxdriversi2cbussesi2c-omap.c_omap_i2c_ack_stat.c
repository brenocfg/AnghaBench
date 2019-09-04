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
typedef  int /*<<< orphan*/  u16 ;
struct omap_i2c_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_I2C_STAT_REG ; 
 int /*<<< orphan*/  omap_i2c_write_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
omap_i2c_ack_stat(struct omap_i2c_dev *omap, u16 stat)
{
	omap_i2c_write_reg(omap, OMAP_I2C_STAT_REG, stat);
}