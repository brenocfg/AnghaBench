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
struct stk1160 {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  STK1160_SBUSR_RA ; 
 int /*<<< orphan*/  STK1160_SICTL ; 
 int /*<<< orphan*/  STK1160_SICTL_SDA ; 
 int stk1160_i2c_busy_wait (struct stk1160*,int) ; 
 int stk1160_write_reg (struct stk1160*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stk1160_i2c_check_for_device(struct stk1160 *dev,
		unsigned char addr)
{
	int rc;

	/* Set serial device address */
	rc = stk1160_write_reg(dev, STK1160_SICTL_SDA, addr);
	if (rc < 0)
		return rc;

	/* Set device sub-address, we'll chip version reg */
	rc = stk1160_write_reg(dev, STK1160_SBUSR_RA, 0x00);
	if (rc < 0)
		return rc;

	/* Start read now */
	rc = stk1160_write_reg(dev, STK1160_SICTL, 0x20);
	if (rc < 0)
		return rc;

	rc = stk1160_i2c_busy_wait(dev, 0x01);
	if (rc < 0)
		return -ENODEV;

	return 0;
}