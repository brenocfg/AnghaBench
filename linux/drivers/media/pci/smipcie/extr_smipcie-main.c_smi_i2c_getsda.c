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
 int SW_I2C_MSK_DAT_IN ; 
 int /*<<< orphan*/  smi_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smi_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int smi_i2c_getsda(void *data, u32 sw_ctl)
{
	struct smi_dev *dev = data;
	/* set as input.*/
	smi_clear(sw_ctl, SW_I2C_MSK_DAT_EN);
	udelay(1);
	return (smi_read(sw_ctl) & SW_I2C_MSK_DAT_IN) ? 1 : 0;
}