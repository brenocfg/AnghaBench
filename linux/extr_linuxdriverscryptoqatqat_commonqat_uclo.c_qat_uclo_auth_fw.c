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
typedef  int u64 ;
struct icp_qat_fw_loader_handle {int dummy; } ;
struct icp_qat_fw_auth_desc {int /*<<< orphan*/  css_hdr_low; int /*<<< orphan*/  css_hdr_high; } ;
struct icp_qat_auth_chunk {int dummy; } ;

/* Variables and functions */
 int ADD_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BITS_IN_DWORD ; 
 int EINVAL ; 
 unsigned int FCU_AUTH_STS_MASK ; 
 int /*<<< orphan*/  FCU_CONTROL ; 
 int FCU_CTRL_CMD_AUTH ; 
 int /*<<< orphan*/  FCU_DRAM_ADDR_HI ; 
 int /*<<< orphan*/  FCU_DRAM_ADDR_LO ; 
 int /*<<< orphan*/  FCU_STATUS ; 
 unsigned int FCU_STS_AUTHFWLD_POS ; 
 unsigned int FCU_STS_VERI_DONE ; 
 unsigned int FCU_STS_VERI_FAIL ; 
 int /*<<< orphan*/  FW_AUTH_MAX_RETRY ; 
 int /*<<< orphan*/  FW_AUTH_WAIT_PERIOD ; 
 unsigned int GET_CAP_CSR (struct icp_qat_fw_loader_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_CAP_CSR (struct icp_qat_fw_loader_handle*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int qat_uclo_auth_fw(struct icp_qat_fw_loader_handle *handle,
			    struct icp_qat_fw_auth_desc *desc)
{
	unsigned int fcu_sts, retry = 0;
	u64 bus_addr;

	bus_addr = ADD_ADDR(desc->css_hdr_high, desc->css_hdr_low)
			   - sizeof(struct icp_qat_auth_chunk);
	SET_CAP_CSR(handle, FCU_DRAM_ADDR_HI, (bus_addr >> BITS_IN_DWORD));
	SET_CAP_CSR(handle, FCU_DRAM_ADDR_LO, bus_addr);
	SET_CAP_CSR(handle, FCU_CONTROL, FCU_CTRL_CMD_AUTH);

	do {
		msleep(FW_AUTH_WAIT_PERIOD);
		fcu_sts = GET_CAP_CSR(handle, FCU_STATUS);
		if ((fcu_sts & FCU_AUTH_STS_MASK) == FCU_STS_VERI_FAIL)
			goto auth_fail;
		if (((fcu_sts >> FCU_STS_AUTHFWLD_POS) & 0x1))
			if ((fcu_sts & FCU_AUTH_STS_MASK) == FCU_STS_VERI_DONE)
				return 0;
	} while (retry++ < FW_AUTH_MAX_RETRY);
auth_fail:
	pr_err("QAT: authentication error (FCU_STATUS = 0x%x),retry = %d\n",
	       fcu_sts & FCU_AUTH_STS_MASK, retry);
	return -EINVAL;
}