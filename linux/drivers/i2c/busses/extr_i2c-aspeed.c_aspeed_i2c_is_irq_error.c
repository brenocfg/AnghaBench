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
typedef  int u32 ;

/* Variables and functions */
 int ASPEED_I2CD_INTR_ABNORMAL ; 
 int ASPEED_I2CD_INTR_ARBIT_LOSS ; 
 int ASPEED_I2CD_INTR_SCL_TIMEOUT ; 
 int ASPEED_I2CD_INTR_SDA_DL_TIMEOUT ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EPROTO ; 

__attribute__((used)) static int aspeed_i2c_is_irq_error(u32 irq_status)
{
	if (irq_status & ASPEED_I2CD_INTR_ARBIT_LOSS)
		return -EAGAIN;
	if (irq_status & (ASPEED_I2CD_INTR_SDA_DL_TIMEOUT |
			  ASPEED_I2CD_INTR_SCL_TIMEOUT))
		return -EBUSY;
	if (irq_status & (ASPEED_I2CD_INTR_ABNORMAL))
		return -EPROTO;

	return 0;
}