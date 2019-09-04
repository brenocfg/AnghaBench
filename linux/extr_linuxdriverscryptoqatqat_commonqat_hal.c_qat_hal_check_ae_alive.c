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
struct icp_qat_fw_loader_handle {TYPE_1__* hal_handle; } ;
struct TYPE_2__ {unsigned char ae_max_num; } ;

/* Variables and functions */
 int EFAULT ; 
 int MAX_RETRY_TIMES ; 
 int /*<<< orphan*/  PROFILE_COUNT ; 
 int /*<<< orphan*/  pr_err (char*,unsigned char) ; 
 unsigned int qat_hal_rd_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qat_hal_check_ae_alive(struct icp_qat_fw_loader_handle *handle)
{
	unsigned int base_cnt, cur_cnt;
	unsigned char ae;
	int times = MAX_RETRY_TIMES;

	for (ae = 0; ae < handle->hal_handle->ae_max_num; ae++) {
		base_cnt = qat_hal_rd_ae_csr(handle, ae, PROFILE_COUNT);
		base_cnt &= 0xffff;

		do {
			cur_cnt = qat_hal_rd_ae_csr(handle, ae, PROFILE_COUNT);
			cur_cnt &= 0xffff;
		} while (times-- && (cur_cnt == base_cnt));

		if (times < 0) {
			pr_err("QAT: AE%d is inactive!!\n", ae);
			return -EFAULT;
		}
	}

	return 0;
}