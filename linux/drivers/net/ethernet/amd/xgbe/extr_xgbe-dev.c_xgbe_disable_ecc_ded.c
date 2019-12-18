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
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_DED ; 
 int /*<<< orphan*/  RX_DED ; 
 int /*<<< orphan*/  TX_DED ; 
 int /*<<< orphan*/  XP_ECC_IER ; 
 unsigned int XP_IOREAD (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XP_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XP_SET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_disable_ecc_ded(struct xgbe_prv_data *pdata)
{
	unsigned int ecc_ier;

	ecc_ier = XP_IOREAD(pdata, XP_ECC_IER);

	/* Disable ECC DED interrupts */
	XP_SET_BITS(ecc_ier, XP_ECC_IER, TX_DED, 0);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, RX_DED, 0);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, DESC_DED, 0);

	XP_IOWRITE(pdata, XP_ECC_IER, ecc_ier);
}