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
typedef  enum xgbe_ecc_sec { ____Placeholder_xgbe_ecc_sec } xgbe_ecc_sec ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_SEC ; 
 int /*<<< orphan*/  RX_SEC ; 
 int /*<<< orphan*/  TX_SEC ; 
#define  XGBE_ECC_SEC_DESC 130 
#define  XGBE_ECC_SEC_RX 129 
#define  XGBE_ECC_SEC_TX 128 
 int /*<<< orphan*/  XP_ECC_IER ; 
 unsigned int XP_IOREAD (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XP_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XP_SET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_disable_ecc_sec(struct xgbe_prv_data *pdata,
				 enum xgbe_ecc_sec sec)
{
	unsigned int ecc_ier;

	ecc_ier = XP_IOREAD(pdata, XP_ECC_IER);

	/* Disable ECC SEC interrupt */
	switch (sec) {
	case XGBE_ECC_SEC_TX:
	XP_SET_BITS(ecc_ier, XP_ECC_IER, TX_SEC, 0);
		break;
	case XGBE_ECC_SEC_RX:
	XP_SET_BITS(ecc_ier, XP_ECC_IER, RX_SEC, 0);
		break;
	case XGBE_ECC_SEC_DESC:
	XP_SET_BITS(ecc_ier, XP_ECC_IER, DESC_SEC, 0);
		break;
	}

	XP_IOWRITE(pdata, XP_ECC_IER, ecc_ier);
}