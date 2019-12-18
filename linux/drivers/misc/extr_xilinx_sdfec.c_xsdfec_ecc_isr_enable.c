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
struct xsdfec_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int XSDFEC_ALL_ECC_ISR_MASK ; 
 int /*<<< orphan*/  XSDFEC_ECC_IDR_ADDR ; 
 int /*<<< orphan*/  XSDFEC_ECC_IER_ADDR ; 
 int /*<<< orphan*/  XSDFEC_ECC_IMR_ADDR ; 
 int XSDFEC_ECC_ISR_MASK ; 
 int XSDFEC_PL_INIT_ECC_ISR_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int xsdfec_regread (struct xsdfec_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsdfec_regwrite (struct xsdfec_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xsdfec_ecc_isr_enable(struct xsdfec_dev *xsdfec, bool enable)
{
	u32 mask_read;

	if (enable) {
		/* Enable */
		xsdfec_regwrite(xsdfec, XSDFEC_ECC_IER_ADDR,
				XSDFEC_ALL_ECC_ISR_MASK);
		mask_read = xsdfec_regread(xsdfec, XSDFEC_ECC_IMR_ADDR);
		if (mask_read & XSDFEC_ALL_ECC_ISR_MASK) {
			dev_dbg(xsdfec->dev,
				"SDFEC enabling ECC irq with ECC IER failed");
			return -EIO;
		}
	} else {
		/* Disable */
		xsdfec_regwrite(xsdfec, XSDFEC_ECC_IDR_ADDR,
				XSDFEC_ALL_ECC_ISR_MASK);
		mask_read = xsdfec_regread(xsdfec, XSDFEC_ECC_IMR_ADDR);
		if (!(((mask_read & XSDFEC_ALL_ECC_ISR_MASK) ==
		       XSDFEC_ECC_ISR_MASK) ||
		      ((mask_read & XSDFEC_ALL_ECC_ISR_MASK) ==
		       XSDFEC_PL_INIT_ECC_ISR_MASK))) {
			dev_dbg(xsdfec->dev,
				"SDFEC disable ECC irq with ECC IDR failed");
			return -EIO;
		}
	}
	return 0;
}