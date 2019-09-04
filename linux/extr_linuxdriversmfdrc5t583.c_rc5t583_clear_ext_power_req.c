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
typedef  int uint8_t ;
struct rc5t583_platform_data {scalar_t__ enable_shutdown; } ;
struct rc5t583 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RC5T583_SLPSEQ1 ; 
 int RC5T583_SLPSEQ11 ; 
 int RICOH_ONOFFSEL_REG ; 
 int RICOH_SWCTL_REG ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int rc5t583_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rc5t583_clear_ext_power_req(struct rc5t583 *rc5t583,
	struct rc5t583_platform_data *pdata)
{
	int ret;
	int i;
	uint8_t on_off_val = 0;

	/*  Clear ONOFFSEL register */
	if (pdata->enable_shutdown)
		on_off_val = 0x1;

	ret = rc5t583_write(rc5t583->dev, RICOH_ONOFFSEL_REG, on_off_val);
	if (ret < 0)
		dev_warn(rc5t583->dev, "Error in writing reg %d error: %d\n",
					RICOH_ONOFFSEL_REG, ret);

	ret = rc5t583_write(rc5t583->dev, RICOH_SWCTL_REG, 0x0);
	if (ret < 0)
		dev_warn(rc5t583->dev, "Error in writing reg %d error: %d\n",
					RICOH_SWCTL_REG, ret);

	/* Clear sleep sequence register */
	for (i = RC5T583_SLPSEQ1; i <= RC5T583_SLPSEQ11; ++i) {
		ret = rc5t583_write(rc5t583->dev, i, 0x0);
		if (ret < 0)
			dev_warn(rc5t583->dev,
				"Error in writing reg 0x%02x error: %d\n",
				i, ret);
	}
	return 0;
}