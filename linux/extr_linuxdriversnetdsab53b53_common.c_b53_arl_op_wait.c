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
struct b53_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARLTBL_START_DONE ; 
 int /*<<< orphan*/  B53_ARLIO_PAGE ; 
 int /*<<< orphan*/  B53_ARLTBL_RW_CTRL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int b53_arl_op_wait(struct b53_device *dev)
{
	unsigned int timeout = 10;
	u8 reg;

	do {
		b53_read8(dev, B53_ARLIO_PAGE, B53_ARLTBL_RW_CTRL, &reg);
		if (!(reg & ARLTBL_START_DONE))
			return 0;

		usleep_range(1000, 2000);
	} while (timeout--);

	dev_warn(dev->dev, "timeout waiting for ARL to finish: 0x%02x\n", reg);

	return -ETIMEDOUT;
}