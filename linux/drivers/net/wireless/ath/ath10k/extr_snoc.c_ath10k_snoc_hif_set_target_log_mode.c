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
typedef  scalar_t__ u8 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 scalar_t__ ATH10K_ENABLE_FW_LOG_CE ; 
 scalar_t__ ATH10K_ENABLE_FW_LOG_DIAG ; 
 int ath10k_qmi_set_fw_log_mode (struct ath10k*,scalar_t__) ; 

__attribute__((used)) static int ath10k_snoc_hif_set_target_log_mode(struct ath10k *ar,
					       u8 fw_log_mode)
{
	u8 fw_dbg_mode;

	if (fw_log_mode)
		fw_dbg_mode = ATH10K_ENABLE_FW_LOG_CE;
	else
		fw_dbg_mode = ATH10K_ENABLE_FW_LOG_DIAG;

	return ath10k_qmi_set_fw_log_mode(ar, fw_dbg_mode);
}