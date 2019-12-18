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
struct pxa_i2c {int highmode_enter; int master_code; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int HZ ; 
 int I2C_RETRY ; 
 int ICR_ALDIE ; 
 int ICR_GPIOEN ; 
 int ICR_ITEIE ; 
 int ICR_START ; 
 int ICR_STOP ; 
 int ICR_TB ; 
 int /*<<< orphan*/  _ICR (struct pxa_i2c*) ; 
 int /*<<< orphan*/  _IDBR (struct pxa_i2c*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_pxa_send_mastercode(struct pxa_i2c *i2c)
{
	u32 icr;
	long timeout;

	spin_lock_irq(&i2c->lock);
	i2c->highmode_enter = true;
	writel(i2c->master_code, _IDBR(i2c));

	icr = readl(_ICR(i2c)) & ~(ICR_STOP | ICR_ALDIE);
	icr |= ICR_GPIOEN | ICR_START | ICR_TB | ICR_ITEIE;
	writel(icr, _ICR(i2c));

	spin_unlock_irq(&i2c->lock);
	timeout = wait_event_timeout(i2c->wait,
			i2c->highmode_enter == false, HZ * 1);

	i2c->highmode_enter = false;

	return (timeout == 0) ? I2C_RETRY : 0;
}