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
typedef  int /*<<< orphan*/  u32 ;
struct pch_udc_dev {int dummy; } ;

/* Variables and functions */
 unsigned long PCH_UDC_CSR (unsigned int) ; 
 int /*<<< orphan*/  pch_udc_csr_busy (struct pch_udc_dev*) ; 
 int /*<<< orphan*/  pch_udc_readl (struct pch_udc_dev*,unsigned long) ; 

__attribute__((used)) static u32 pch_udc_read_csr(struct pch_udc_dev *dev, unsigned int ep)
{
	unsigned long reg = PCH_UDC_CSR(ep);

	pch_udc_csr_busy(dev);		/* Wait till idle */
	pch_udc_readl(dev, reg);	/* Dummy read */
	pch_udc_csr_busy(dev);		/* Wait till idle */
	return pch_udc_readl(dev, reg);
}