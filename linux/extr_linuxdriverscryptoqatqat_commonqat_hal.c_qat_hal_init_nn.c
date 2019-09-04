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
 int EINVAL ; 
 unsigned char ICP_QAT_UCLO_MAX_CTX ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int qat_hal_put_rel_nn (struct icp_qat_fw_loader_handle*,unsigned char,unsigned char,unsigned short,unsigned int) ; 
 int /*<<< orphan*/  test_bit (unsigned char,unsigned long*) ; 

int qat_hal_init_nn(struct icp_qat_fw_loader_handle *handle,
		    unsigned char ae, unsigned char ctx_mask,
		    unsigned short reg_num, unsigned int regdata)
{
	int stat = 0;
	unsigned char ctx;

	if (ctx_mask == 0)
		return -EINVAL;

	for (ctx = 0; ctx < ICP_QAT_UCLO_MAX_CTX; ctx++) {
		if (!test_bit(ctx, (unsigned long *)&ctx_mask))
			continue;
		stat = qat_hal_put_rel_nn(handle, ae, ctx, reg_num, regdata);
		if (stat) {
			pr_err("QAT: write neigh error\n");
			return -EINVAL;
		}
	}

	return 0;
}