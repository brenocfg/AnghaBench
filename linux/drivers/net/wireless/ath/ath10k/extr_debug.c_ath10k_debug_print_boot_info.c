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
struct TYPE_5__ {int /*<<< orphan*/  htt_op_version; int /*<<< orphan*/  wmi_op_version; } ;
struct TYPE_6__ {TYPE_2__ fw_file; } ;
struct TYPE_4__ {int /*<<< orphan*/  target_version_minor; int /*<<< orphan*/  target_version_major; } ;
struct ath10k {int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  max_num_stations; int /*<<< orphan*/  cal_mode; TYPE_3__ normal_mode_fw; TYPE_1__ htt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FLAG_HW_CRYPTO_DISABLED ; 
 int /*<<< orphan*/  ATH10K_FLAG_RAW_MODE ; 
 int /*<<< orphan*/  ath10k_cal_mode_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_info (struct ath10k*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath10k_debug_print_boot_info(struct ath10k *ar)
{
	ath10k_info(ar, "htt-ver %d.%d wmi-op %d htt-op %d cal %s max-sta %d raw %d hwcrypto %d\n",
		    ar->htt.target_version_major,
		    ar->htt.target_version_minor,
		    ar->normal_mode_fw.fw_file.wmi_op_version,
		    ar->normal_mode_fw.fw_file.htt_op_version,
		    ath10k_cal_mode_str(ar->cal_mode),
		    ar->max_num_stations,
		    test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags),
		    !test_bit(ATH10K_FLAG_HW_CRYPTO_DISABLED, &ar->dev_flags));
}