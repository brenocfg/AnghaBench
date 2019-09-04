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
struct icp_qat_fw_loader_handle {int dummy; } ;

/* Variables and functions */
 unsigned int CSR_RETRY_TIMES ; 
 int GET_AE_CSR (struct icp_qat_fw_loader_handle*,unsigned char,unsigned int) ; 
 int LCS_STATUS ; 
 unsigned int LOCAL_CSR_STATUS ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int qat_hal_rd_ae_csr(struct icp_qat_fw_loader_handle *handle,
			     unsigned char ae, unsigned int csr)
{
	unsigned int iterations = CSR_RETRY_TIMES;
	int value;

	do {
		value = GET_AE_CSR(handle, ae, csr);
		if (!(GET_AE_CSR(handle, ae, LOCAL_CSR_STATUS) & LCS_STATUS))
			return value;
	} while (iterations--);

	pr_err("QAT: Read CSR timeout\n");
	return 0;
}