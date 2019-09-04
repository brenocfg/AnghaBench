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
 int I2C_ERR_ALD ; 
 int I2C_ERR_BERR ; 
 int IOP3XX_ISR_ALD ; 
 int IOP3XX_ISR_BERRD ; 

__attribute__((used)) static int
iop3xx_i2c_error(u32 sr)
{
	int rc = 0;

	if ((sr & IOP3XX_ISR_BERRD)) {
		if ( !rc ) rc = -I2C_ERR_BERR;
	}
	if ((sr & IOP3XX_ISR_ALD)) {
		if ( !rc ) rc = -I2C_ERR_ALD;
	}
	return rc;
}