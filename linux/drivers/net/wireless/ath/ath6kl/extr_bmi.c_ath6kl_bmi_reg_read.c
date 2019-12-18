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
typedef  size_t u32 ;
typedef  int u16 ;
struct TYPE_2__ {int max_cmd_size; size_t* cmd_buf; scalar_t__ done_sent; } ;
struct ath6kl {TYPE_1__ bmi; } ;
typedef  int /*<<< orphan*/  cid ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BMI ; 
 size_t BMI_READ_SOC_REGISTER ; 
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 
 int ath6kl_hif_bmi_read (struct ath6kl*,size_t*,int) ; 
 int ath6kl_hif_bmi_write (struct ath6kl*,size_t*,size_t) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 

int ath6kl_bmi_reg_read(struct ath6kl *ar, u32 addr, u32 *param)
{
	u32 cid = BMI_READ_SOC_REGISTER;
	int ret;
	u32 offset;
	u16 size;

	if (ar->bmi.done_sent) {
		ath6kl_err("bmi done sent already, cmd %d disallowed\n", cid);
		return -EACCES;
	}

	size = sizeof(cid) + sizeof(addr);
	if (size > ar->bmi.max_cmd_size) {
		WARN_ON(1);
		return -EINVAL;
	}
	memset(ar->bmi.cmd_buf, 0, size);

	ath6kl_dbg(ATH6KL_DBG_BMI, "bmi read SOC reg: addr: 0x%x\n", addr);

	offset = 0;
	memcpy(&(ar->bmi.cmd_buf[offset]), &cid, sizeof(cid));
	offset += sizeof(cid);
	memcpy(&(ar->bmi.cmd_buf[offset]), &addr, sizeof(addr));
	offset += sizeof(addr);

	ret = ath6kl_hif_bmi_write(ar, ar->bmi.cmd_buf, offset);
	if (ret) {
		ath6kl_err("Unable to write to the device: %d\n", ret);
		return ret;
	}

	ret = ath6kl_hif_bmi_read(ar, ar->bmi.cmd_buf, sizeof(*param));
	if (ret) {
		ath6kl_err("Unable to read from the device: %d\n", ret);
		return ret;
	}
	memcpy(param, ar->bmi.cmd_buf, sizeof(*param));

	return 0;
}