#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct pxa_i2c {TYPE_1__ adap; } ;

/* Variables and functions */
 int DEF_TIMEOUT ; 
 int I2C_RETRY ; 
 int ICR_SCLE ; 
 int ISR_IBB ; 
 int ISR_UB ; 
 int /*<<< orphan*/  _ICR (struct pxa_i2c*) ; 
 int /*<<< orphan*/  _ISR (struct pxa_i2c*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_state (struct pxa_i2c*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_pxa_pio_set_master(struct pxa_i2c *i2c)
{
	/* make timeout the same as for interrupt based functions */
	long timeout = 2 * DEF_TIMEOUT;

	/*
	 * Wait for the bus to become free.
	 */
	while (timeout-- && readl(_ISR(i2c)) & (ISR_IBB | ISR_UB)) {
		udelay(1000);
		show_state(i2c);
	}

	if (timeout < 0) {
		show_state(i2c);
		dev_err(&i2c->adap.dev,
			"i2c_pxa: timeout waiting for bus free\n");
		return I2C_RETRY;
	}

	/*
	 * Set master mode.
	 */
	writel(readl(_ICR(i2c)) | ICR_SCLE, _ICR(i2c));

	return 0;
}