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
typedef  int u32 ;
struct tc_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int AUX_BUSY ; 
 int AUX_STATUS_MASK ; 
 int AUX_STATUS_SHIFT ; 
 int AUX_TIMEOUT ; 
 int /*<<< orphan*/  DP0_AUXSTATUS ; 
 int EBUSY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int tc_aux_get_status(struct tc_data *tc, u8 *reply)
{
	int ret;
	u32 value;

	ret = regmap_read(tc->regmap, DP0_AUXSTATUS, &value);
	if (ret < 0)
		return ret;
	if (value & AUX_BUSY) {
		if (value & AUX_TIMEOUT) {
			dev_err(tc->dev, "i2c access timeout!\n");
			return -ETIMEDOUT;
		}
		return -EBUSY;
	}

	*reply = (value & AUX_STATUS_MASK) >> AUX_STATUS_SHIFT;
	return 0;
}