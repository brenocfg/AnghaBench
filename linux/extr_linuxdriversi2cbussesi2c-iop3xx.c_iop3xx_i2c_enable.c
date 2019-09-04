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
struct i2c_algo_iop3xx_data {int SR_enabled; scalar_t__ ioaddr; } ;

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

__attribute__((used)) static void
iop3xx_i2c_enable(struct i2c_algo_iop3xx_data *iop3xx_adap)
{
	u32 cr = IOP3XX_ICR_GCD | IOP3XX_ICR_SCLEN | IOP3XX_ICR_UE;

	/*
	 * Every time unit enable is asserted, GPOD needs to be cleared
	 * on IOP3XX to avoid data corruption on the bus.
	 */
#if defined(CONFIG_ARCH_IOP32X) || defined(CONFIG_ARCH_IOP33X)
	if (iop3xx_adap->id == 0) {
		gpio_set_value(7, 0);
		gpio_set_value(6, 0);
	} else {
		gpio_set_value(5, 0);
		gpio_set_value(4, 0);
	}
#endif
	/* NB SR bits not same position as CR IE bits :-( */
	iop3xx_adap->SR_enabled =
		IOP3XX_ISR_ALD | IOP3XX_ISR_BERRD |
		IOP3XX_ISR_RXFULL | IOP3XX_ISR_TXEMPTY;

	cr |= IOP3XX_ICR_ALD_IE | IOP3XX_ICR_BERR_IE |
		IOP3XX_ICR_RXFULL_IE | IOP3XX_ICR_TXEMPTY_IE;

	__raw_writel(cr, iop3xx_adap->ioaddr + CR_OFFSET);
}