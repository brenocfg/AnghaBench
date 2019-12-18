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
struct isp1301 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP1301_I2C_REG_CLEAR_ADDR ; 
 int __isp1301_write (struct isp1301*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isp1301_clear(struct isp1301 *isp, u8 reg, u8 value)
{
	return __isp1301_write(isp, reg, value, ISP1301_I2C_REG_CLEAR_ADDR);
}