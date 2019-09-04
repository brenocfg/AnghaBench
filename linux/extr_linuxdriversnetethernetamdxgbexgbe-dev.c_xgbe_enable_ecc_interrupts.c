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
struct xgbe_prv_data {TYPE_1__* vdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  ecc_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_DED ; 
 int /*<<< orphan*/  DESC_SEC ; 
 int /*<<< orphan*/  RX_DED ; 
 int /*<<< orphan*/  RX_SEC ; 
 int /*<<< orphan*/  TX_DED ; 
 int /*<<< orphan*/  TX_SEC ; 
 int /*<<< orphan*/  XP_ECC_IER ; 
 int /*<<< orphan*/  XP_ECC_ISR ; 
 unsigned int XP_IOREAD (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XP_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XP_SET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgbe_enable_ecc_interrupts(struct xgbe_prv_data *pdata)
{
	unsigned int ecc_isr, ecc_ier = 0;

	if (!pdata->vdata->ecc_support)
		return;

	/* Clear all the interrupts which are set */
	ecc_isr = XP_IOREAD(pdata, XP_ECC_ISR);
	XP_IOWRITE(pdata, XP_ECC_ISR, ecc_isr);

	/* Enable ECC interrupts */
	XP_SET_BITS(ecc_ier, XP_ECC_IER, TX_DED, 1);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, TX_SEC, 1);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, RX_DED, 1);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, RX_SEC, 1);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, DESC_DED, 1);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, DESC_SEC, 1);

	XP_IOWRITE(pdata, XP_ECC_IER, ecc_ier);
}