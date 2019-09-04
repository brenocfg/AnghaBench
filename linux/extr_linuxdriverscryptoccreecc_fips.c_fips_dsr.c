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
struct device {int dummy; } ;
struct cc_drvdata {int irq; } ;

/* Variables and functions */
 int CC_FIPS_SYNC_MODULE_OK ; 
 int CC_FIPS_SYNC_TEE_STATUS ; 
 int CC_GPR0_IRQ_MASK ; 
 int CC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPR_HOST ; 
 int /*<<< orphan*/  HOST_IMR ; 
 int cc_ioread (struct cc_drvdata*,int) ; 
 int /*<<< orphan*/  cc_iowrite (struct cc_drvdata*,int,int) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int /*<<< orphan*/  tee_fips_error (struct device*) ; 

__attribute__((used)) static void fips_dsr(unsigned long devarg)
{
	struct cc_drvdata *drvdata = (struct cc_drvdata *)devarg;
	struct device *dev = drvdata_to_dev(drvdata);
	u32 irq, state, val;

	irq = (drvdata->irq & (CC_GPR0_IRQ_MASK));

	if (irq) {
		state = cc_ioread(drvdata, CC_REG(GPR_HOST));

		if (state != (CC_FIPS_SYNC_TEE_STATUS | CC_FIPS_SYNC_MODULE_OK))
			tee_fips_error(dev);
	}

	/* after verifing that there is nothing to do,
	 * unmask AXI completion interrupt.
	 */
	val = (CC_REG(HOST_IMR) & ~irq);
	cc_iowrite(drvdata, CC_REG(HOST_IMR), val);
}