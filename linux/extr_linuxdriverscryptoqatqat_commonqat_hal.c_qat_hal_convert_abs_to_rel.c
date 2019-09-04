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
 unsigned int CE_INUSE_CONTEXTS ; 
 int /*<<< orphan*/  CTX_ENABLES ; 
 unsigned int qat_hal_rd_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qat_hal_convert_abs_to_rel(struct icp_qat_fw_loader_handle
				      *handle, unsigned char ae,
				      unsigned short absreg_num,
				      unsigned short *relreg,
				      unsigned char *ctx)
{
	unsigned int ctx_enables;

	ctx_enables = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	if (ctx_enables & CE_INUSE_CONTEXTS) {
		/* 4-ctx mode */
		*relreg = absreg_num & 0x1F;
		*ctx = (absreg_num >> 0x4) & 0x6;
	} else {
		/* 8-ctx mode */
		*relreg = absreg_num & 0x0F;
		*ctx = (absreg_num >> 0x4) & 0x7;
	}
	return 0;
}