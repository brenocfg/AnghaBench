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
 unsigned int CSR_CTX_POINTER ; 
 unsigned int ICP_QAT_UCLO_MAX_CTX ; 
 unsigned int qat_hal_rd_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  qat_hal_wr_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,unsigned int,unsigned int) ; 

__attribute__((used)) static void qat_hal_wr_indr_csr(struct icp_qat_fw_loader_handle *handle,
				unsigned char ae, unsigned int ctx_mask,
				unsigned int ae_csr, unsigned int csr_val)
{
	unsigned int ctx, cur_ctx;

	cur_ctx = qat_hal_rd_ae_csr(handle, ae, CSR_CTX_POINTER);

	for (ctx = 0; ctx < ICP_QAT_UCLO_MAX_CTX; ctx++) {
		if (!(ctx_mask & (1 << ctx)))
			continue;
		qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, ctx);
		qat_hal_wr_ae_csr(handle, ae, ae_csr, csr_val);
	}

	qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, cur_ctx);
}