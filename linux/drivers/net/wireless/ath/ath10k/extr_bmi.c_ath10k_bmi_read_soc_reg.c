#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
union bmi_resp {TYPE_3__ read_soc_reg; } ;
typedef  int u32 ;
struct TYPE_5__ {void* addr; } ;
struct bmi_cmd {TYPE_2__ read_soc_reg; void* id; } ;
struct TYPE_4__ {scalar_t__ done_sent; } ;
struct ath10k {TYPE_1__ bmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BMI ; 
 int BMI_READ_SOC_REGISTER ; 
 int EBUSY ; 
 void* __cpu_to_le32 (int) ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int) ; 
 int ath10k_hif_exchange_bmi_msg (struct ath10k*,struct bmi_cmd*,int,union bmi_resp*,int*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 

int ath10k_bmi_read_soc_reg(struct ath10k *ar, u32 address, u32 *reg_val)
{
	struct bmi_cmd cmd;
	union bmi_resp resp;
	u32 cmdlen = sizeof(cmd.id) + sizeof(cmd.read_soc_reg);
	u32 resplen = sizeof(resp.read_soc_reg);
	int ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi read soc register 0x%08x\n",
		   address);

	if (ar->bmi.done_sent) {
		ath10k_warn(ar, "bmi read soc register command in progress\n");
		return -EBUSY;
	}

	cmd.id = __cpu_to_le32(BMI_READ_SOC_REGISTER);
	cmd.read_soc_reg.addr = __cpu_to_le32(address);

	ret = ath10k_hif_exchange_bmi_msg(ar, &cmd, cmdlen, &resp, &resplen);
	if (ret) {
		ath10k_warn(ar, "Unable to read soc register from device: %d\n",
			    ret);
		return ret;
	}

	*reg_val = __le32_to_cpu(resp.read_soc_reg.value);

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi read soc register value 0x%08x\n",
		   *reg_val);

	return 0;
}