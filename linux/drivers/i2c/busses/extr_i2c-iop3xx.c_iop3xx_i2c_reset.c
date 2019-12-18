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
struct i2c_algo_iop3xx_data {scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ CR_OFFSET ; 
 int /*<<< orphan*/  IOP3XX_ICR_UNIT_RESET ; 
 int /*<<< orphan*/  IOP3XX_ISR_CLEARBITS ; 
 scalar_t__ SR_OFFSET ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
iop3xx_i2c_reset(struct i2c_algo_iop3xx_data *iop3xx_adap)
{
	/* Follows devman 9.3 */
	__raw_writel(IOP3XX_ICR_UNIT_RESET, iop3xx_adap->ioaddr + CR_OFFSET);
	__raw_writel(IOP3XX_ISR_CLEARBITS, iop3xx_adap->ioaddr + SR_OFFSET);
	__raw_writel(0, iop3xx_adap->ioaddr + CR_OFFSET);
}