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
struct smi_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW_I2C_MSK_DAT_EN ; 
 int /*<<< orphan*/  SW_I2C_MSK_DAT_OUT ; 
 int /*<<< orphan*/  smi_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smi_i2c_setsda(struct smi_dev *dev, int state, u32 sw_ctl)
{
	if (state) {
		/* set as input.*/
		smi_clear(sw_ctl, SW_I2C_MSK_DAT_EN);
	} else {
		smi_clear(sw_ctl, SW_I2C_MSK_DAT_OUT);
		/* set as output.*/
		smi_set(sw_ctl, SW_I2C_MSK_DAT_EN);
	}
}