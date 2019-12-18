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
struct fusb302_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB_REG_CONTROL3 ; 
 int FUSB_REG_CONTROL3_AUTO_RETRY ; 
 int FUSB_REG_CONTROL3_N_RETRIES_3 ; 
 int fusb302_i2c_set_bits (struct fusb302_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fusb302_enable_tx_auto_retries(struct fusb302_chip *chip)
{
	int ret = 0;

	ret = fusb302_i2c_set_bits(chip, FUSB_REG_CONTROL3,
				   FUSB_REG_CONTROL3_N_RETRIES_3 |
				   FUSB_REG_CONTROL3_AUTO_RETRY);

	return ret;
}