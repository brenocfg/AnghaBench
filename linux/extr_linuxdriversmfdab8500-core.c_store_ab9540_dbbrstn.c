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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ab8500 {int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_REGU_CTRL2 ; 
 int /*<<< orphan*/  AB9540_MODEM_CTRL2_REG ; 
 int /*<<< orphan*/  AB9540_MODEM_CTRL2_SWDBBRSTN_BIT ; 
 struct ab8500* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char const,int) ; 
 int mask_and_set_register_interruptible (struct ab8500*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store_ab9540_dbbrstn(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct ab8500 *ab8500;
	int ret = count;
	int err;
	u8 bitvalues;

	ab8500 = dev_get_drvdata(dev);

	if (count > 0) {
		switch (buf[0]) {
		case '0':
			bitvalues = 0;
			break;
		case '1':
			bitvalues = AB9540_MODEM_CTRL2_SWDBBRSTN_BIT;
			break;
		default:
			goto exit;
		}

		err = mask_and_set_register_interruptible(ab8500,
			AB8500_REGU_CTRL2, AB9540_MODEM_CTRL2_REG,
			AB9540_MODEM_CTRL2_SWDBBRSTN_BIT, bitvalues);
		if (err)
			dev_info(ab8500->dev,
				"Failed to set DBBRSTN %c, err %#x\n",
				buf[0], err);
	}

exit:
	return ret;
}