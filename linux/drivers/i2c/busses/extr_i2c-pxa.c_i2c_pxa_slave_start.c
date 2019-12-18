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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct pxa_i2c {TYPE_1__ adap; } ;

/* Variables and functions */
 int ICR_ACKNAK ; 
 int ICR_SCLE ; 
 int ICR_START ; 
 int ICR_STOP ; 
 int ICR_TB ; 
 int /*<<< orphan*/  _IBMR (struct pxa_i2c*) ; 
 int /*<<< orphan*/  _ICR (struct pxa_i2c*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2c_pxa_slave_start(struct pxa_i2c *i2c, u32 isr)
{
	int timeout;

	/*
	 * slave could interrupt in the middle of us generating a
	 * start condition... if this happens, we'd better back off
	 * and stop holding the poor thing up
	 */
	writel(readl(_ICR(i2c)) & ~(ICR_START|ICR_STOP), _ICR(i2c));
	writel(readl(_ICR(i2c)) | ICR_TB | ICR_ACKNAK, _ICR(i2c));

	timeout = 0x10000;

	while (1) {
		if ((readl(_IBMR(i2c)) & 2) == 2)
			break;

		timeout--;

		if (timeout <= 0) {
			dev_err(&i2c->adap.dev, "timeout waiting for SCL high\n");
			break;
		}
	}

	writel(readl(_ICR(i2c)) & ~ICR_SCLE, _ICR(i2c));
}