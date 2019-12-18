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
struct i2c_algo_iop3xx_data {int SR_enabled; scalar_t__ ioaddr; scalar_t__ gpio_sda; scalar_t__ gpio_scl; } ;

/* Variables and functions */
 scalar_t__ CR_OFFSET ; 
 int IOP3XX_ICR_ALD_IE ; 
 int IOP3XX_ICR_BERR_IE ; 
 int IOP3XX_ICR_GCD ; 
 int IOP3XX_ICR_RXFULL_IE ; 
 int IOP3XX_ICR_SCLEN ; 
 int IOP3XX_ICR_TXEMPTY_IE ; 
 int IOP3XX_ICR_UE ; 
 int IOP3XX_ISR_ALD ; 
 int IOP3XX_ISR_BERRD ; 
 int IOP3XX_ISR_RXFULL ; 
 int IOP3XX_ISR_TXEMPTY ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  gpiod_set_raw_value (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iop3xx_i2c_enable(struct i2c_algo_iop3xx_data *iop3xx_adap)
{
	u32 cr = IOP3XX_ICR_GCD | IOP3XX_ICR_SCLEN | IOP3XX_ICR_UE;

	/*
	 * Every time unit enable is asserted, GPOD needs to be cleared
	 * on IOP3XX to avoid data corruption on the bus. We use the
	 * gpiod_set_raw_value() to make sure the 0 hits the hardware
	 * GPOD register. These descriptors are only passed along to
	 * the device if this is necessary.
	 */
	if (iop3xx_adap->gpio_scl)
		gpiod_set_raw_value(iop3xx_adap->gpio_scl, 0);
	if (iop3xx_adap->gpio_sda)
		gpiod_set_raw_value(iop3xx_adap->gpio_sda, 0);

	/* NB SR bits not same position as CR IE bits :-( */
	iop3xx_adap->SR_enabled =
		IOP3XX_ISR_ALD | IOP3XX_ISR_BERRD |
		IOP3XX_ISR_RXFULL | IOP3XX_ISR_TXEMPTY;

	cr |= IOP3XX_ICR_ALD_IE | IOP3XX_ICR_BERR_IE |
		IOP3XX_ICR_RXFULL_IE | IOP3XX_ICR_TXEMPTY_IE;

	__raw_writel(cr, iop3xx_adap->ioaddr + CR_OFFSET);
}