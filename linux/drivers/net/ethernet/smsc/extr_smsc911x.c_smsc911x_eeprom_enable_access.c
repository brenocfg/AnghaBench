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
struct smsc911x_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CFG ; 
 unsigned int GPIO_CFG_EEPR_EN_ ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void smsc911x_eeprom_enable_access(struct smsc911x_data *pdata)
{
	unsigned int temp = smsc911x_reg_read(pdata, GPIO_CFG);
	temp &= ~GPIO_CFG_EEPR_EN_;
	smsc911x_reg_write(pdata, GPIO_CFG, temp);
	msleep(1);
}