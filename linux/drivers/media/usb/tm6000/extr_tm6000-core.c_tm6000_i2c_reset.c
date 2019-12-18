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
struct tm6000_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_03_SET_GET_MCU_PIN ; 
 int /*<<< orphan*/  TM6000_GPIO_CLK ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int tm6000_set_reg (struct tm6000_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int tm6000_i2c_reset(struct tm6000_core *dev, u16 tsleep)
{
	int rc;

	rc = tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, TM6000_GPIO_CLK, 0);
	if (rc < 0)
		return rc;

	msleep(tsleep);

	rc = tm6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, TM6000_GPIO_CLK, 1);
	msleep(tsleep);

	return rc;
}