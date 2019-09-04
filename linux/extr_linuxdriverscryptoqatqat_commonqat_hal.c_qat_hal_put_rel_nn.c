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
 unsigned int CE_NN_MODE ; 
 int /*<<< orphan*/  CTX_ENABLES ; 
 int /*<<< orphan*/  ICP_NEIGH_REL ; 
 unsigned int IGNORE_W1C_MASK ; 
 int qat_hal_put_rel_wr_xfer (struct icp_qat_fw_loader_handle*,unsigned char,unsigned char,int /*<<< orphan*/ ,unsigned short,unsigned int) ; 
 unsigned int qat_hal_rd_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qat_hal_wr_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int qat_hal_put_rel_nn(struct icp_qat_fw_loader_handle *handle,
			      unsigned char ae, unsigned char ctx,
			      unsigned short nn, unsigned int val)
{
	unsigned int ctx_enables;
	int stat = 0;

	ctx_enables = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	ctx_enables &= IGNORE_W1C_MASK;
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, ctx_enables | CE_NN_MODE);

	stat = qat_hal_put_rel_wr_xfer(handle, ae, ctx, ICP_NEIGH_REL, nn, val);
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, ctx_enables);
	return stat;
}