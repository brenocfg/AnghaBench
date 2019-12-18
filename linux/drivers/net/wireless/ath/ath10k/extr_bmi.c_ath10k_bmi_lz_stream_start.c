#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {void* addr; } ;
struct bmi_cmd {TYPE_2__ lz_start; void* id; } ;
struct TYPE_3__ {scalar_t__ done_sent; } ;
struct ath10k {TYPE_1__ bmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BMI ; 
 int BMI_LZ_STREAM_START ; 
 int EBUSY ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int) ; 
 int ath10k_hif_exchange_bmi_msg (struct ath10k*,struct bmi_cmd*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 

int ath10k_bmi_lz_stream_start(struct ath10k *ar, u32 address)
{
	struct bmi_cmd cmd;
	u32 cmdlen = sizeof(cmd.id) + sizeof(cmd.lz_start);
	int ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi lz stream start address 0x%x\n",
		   address);

	if (ar->bmi.done_sent) {
		ath10k_warn(ar, "command disallowed\n");
		return -EBUSY;
	}

	cmd.id            = __cpu_to_le32(BMI_LZ_STREAM_START);
	cmd.lz_start.addr = __cpu_to_le32(address);

	ret = ath10k_hif_exchange_bmi_msg(ar, &cmd, cmdlen, NULL, NULL);
	if (ret) {
		ath10k_warn(ar, "unable to Start LZ Stream to the device\n");
		return ret;
	}

	return 0;
}