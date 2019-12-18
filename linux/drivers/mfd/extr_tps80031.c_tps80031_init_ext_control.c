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
struct tps80031_platform_data {int dummy; } ;
struct tps80031 {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TPS80031_PHOENIX_MSK_TRANSITION ; 
 scalar_t__ TPS80031_PREQ1_RES_ASS_A ; 
 int /*<<< orphan*/  TPS80031_SLAVE_ID1 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,int) ; 
 int tps80031_set_bits (struct device*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int tps80031_write (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps80031_init_ext_control(struct tps80031 *tps80031,
			struct tps80031_platform_data *pdata)
{
	struct device *dev = tps80031->dev;
	int ret;
	int i;

	/* Clear all external control for this rail */
	for (i = 0; i < 9; ++i) {
		ret = tps80031_write(dev, TPS80031_SLAVE_ID1,
				TPS80031_PREQ1_RES_ASS_A + i, 0);
		if (ret < 0) {
			dev_err(dev, "reg 0x%02x write failed, err = %d\n",
				TPS80031_PREQ1_RES_ASS_A + i, ret);
			return ret;
		}
	}

	/* Mask the PREQ */
	ret = tps80031_set_bits(dev, TPS80031_SLAVE_ID1,
			TPS80031_PHOENIX_MSK_TRANSITION, 0x7 << 5);
	if (ret < 0) {
		dev_err(dev, "reg 0x%02x set_bits failed, err = %d\n",
			TPS80031_PHOENIX_MSK_TRANSITION, ret);
		return ret;
	}
	return ret;
}