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
 int /*<<< orphan*/  CSR_CTX_POINTER ; 
 int /*<<< orphan*/  CTX_WAKEUP_EVENTS_INDIRECT ; 
 unsigned int qat_hal_rd_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qat_hal_wr_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void qat_hal_get_wakeup_event(struct icp_qat_fw_loader_handle *handle,
				     unsigned char ae, unsigned char ctx,
				     unsigned int *events)
{
	unsigned int cur_ctx;

	cur_ctx = qat_hal_rd_ae_csr(handle, ae, CSR_CTX_POINTER);
	qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, ctx);
	*events = qat_hal_rd_ae_csr(handle, ae, CTX_WAKEUP_EVENTS_INDIRECT);
	qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, cur_ctx);
}