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
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_read (struct regmap*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lan9303_read(struct regmap *regmap, unsigned int offset, u32 *reg)
{
	int ret, i;

	/* we can lose arbitration for the I2C case, because the device
	 * tries to detect and read an external EEPROM after reset and acts as
	 * a master on the shared I2C bus itself. This conflicts with our
	 * attempts to access the device as a slave at the same moment.
	 */
	for (i = 0; i < 5; i++) {
		ret = regmap_read(regmap, offset, reg);
		if (!ret)
			return 0;
		if (ret != -EAGAIN)
			break;
		msleep(500);
	}

	return -EIO;
}