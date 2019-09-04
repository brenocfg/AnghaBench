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
typedef  int /*<<< orphan*/  u8 ;
struct intel_msic {unsigned short irq_base; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned short INTEL_MSIC_IRQLVL1 ; 
 unsigned short INTEL_MSIC_RESETIRQ2 ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  readb (unsigned short) ; 

int intel_msic_irq_read(struct intel_msic *msic, unsigned short reg, u8 *val)
{
	if (WARN_ON(reg < INTEL_MSIC_IRQLVL1 || reg > INTEL_MSIC_RESETIRQ2))
		return -EINVAL;

	*val = readb(msic->irq_base + (reg - INTEL_MSIC_IRQLVL1));
	return 0;
}