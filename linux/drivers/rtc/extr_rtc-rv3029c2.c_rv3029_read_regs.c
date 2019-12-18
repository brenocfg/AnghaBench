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
typedef  scalar_t__ u8 ;
struct rv3029_data {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RV3029_USR1_RAM_PAGE ; 
 struct rv3029_data* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,unsigned int) ; 

__attribute__((used)) static int rv3029_read_regs(struct device *dev, u8 reg, u8 *buf,
			    unsigned int len)
{
	struct rv3029_data *rv3029 = dev_get_drvdata(dev);

	if ((reg > RV3029_USR1_RAM_PAGE + 7) ||
	    (reg + len > RV3029_USR1_RAM_PAGE + 8))
		return -EINVAL;

	return regmap_bulk_read(rv3029->regmap, reg, buf, len);
}