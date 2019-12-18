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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ MISC_CFG_FW_CTRL ; 
 scalar_t__ MISC_CFG_RSA_CMD ; 
 scalar_t__ MISC_CFG_RSA_MODULUS ; 
 scalar_t__ MISC_CFG_RSA_MU ; 
 scalar_t__ MISC_CFG_RSA_R2 ; 
 scalar_t__ MISC_CFG_RSA_SIGNATURE ; 
 scalar_t__ MISC_ERR_CLEAR ; 
 scalar_t__ MISC_ERR_MASK ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,unsigned long long) ; 

__attribute__((used)) static void reset_misc_csrs(struct hfi1_devdata *dd)
{
	int i;

	for (i = 0; i < 32; i++) {
		write_csr(dd, MISC_CFG_RSA_R2 + (8 * i), 0);
		write_csr(dd, MISC_CFG_RSA_SIGNATURE + (8 * i), 0);
		write_csr(dd, MISC_CFG_RSA_MODULUS + (8 * i), 0);
	}
	/*
	 * MISC_CFG_SHA_PRELOAD leave alone - always reads 0 and can
	 * only be written 128-byte chunks
	 */
	/* init RSA engine to clear lingering errors */
	write_csr(dd, MISC_CFG_RSA_CMD, 1);
	write_csr(dd, MISC_CFG_RSA_MU, 0);
	write_csr(dd, MISC_CFG_FW_CTRL, 0);
	/* MISC_STS_8051_DIGEST read-only */
	/* MISC_STS_SBM_DIGEST read-only */
	/* MISC_STS_PCIE_DIGEST read-only */
	/* MISC_STS_FAB_DIGEST read-only */
	/* MISC_ERR_STATUS read-only */
	write_csr(dd, MISC_ERR_MASK, 0);
	write_csr(dd, MISC_ERR_CLEAR, ~0ull);
	/* MISC_ERR_FORCE leave alone */
}