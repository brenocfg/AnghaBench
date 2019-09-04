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

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  IRQ_Ser4SSP ; 
 int MCCR0_MCE ; 
 int PPAR ; 
 int PPAR_SPR ; 
 int /*<<< orphan*/  SSSR_ROR ; 
 int Ser4MCCR0 ; 
 int /*<<< orphan*/  Ser4SSCR0 ; 
 int /*<<< orphan*/  Ser4SSSR ; 
 int /*<<< orphan*/  __PREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  ssp_interrupt ; 

int ssp_init(void)
{
	int ret;

	if (!(PPAR & PPAR_SPR) && (Ser4MCCR0 & MCCR0_MCE))
		return -ENODEV;

	if (!request_mem_region(__PREG(Ser4SSCR0), 0x18, "SSP")) {
		return -EBUSY;
	}

	Ser4SSSR = SSSR_ROR;

	ret = request_irq(IRQ_Ser4SSP, ssp_interrupt, 0, "SSP", NULL);
	if (ret)
		goto out_region;

	return 0;

 out_region:
	release_mem_region(__PREG(Ser4SSCR0), 0x18);
	return ret;
}