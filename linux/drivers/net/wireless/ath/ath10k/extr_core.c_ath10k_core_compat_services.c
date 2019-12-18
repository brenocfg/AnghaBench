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
struct ath10k_fw_file {int wmi_op_version; } ;
struct TYPE_4__ {int /*<<< orphan*/  svc_map; } ;
struct TYPE_3__ {struct ath10k_fw_file fw_file; } ;
struct ath10k {TYPE_2__ wmi; TYPE_1__ normal_mode_fw; } ;

/* Variables and functions */
#define  ATH10K_FW_WMI_OP_VERSION_10_1 131 
#define  ATH10K_FW_WMI_OP_VERSION_10_2 130 
#define  ATH10K_FW_WMI_OP_VERSION_10_2_4 129 
#define  ATH10K_FW_WMI_OP_VERSION_10_4 128 
 int /*<<< orphan*/  WMI_SERVICE_THERM_THROT ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_core_compat_services(struct ath10k *ar)
{
	struct ath10k_fw_file *fw_file = &ar->normal_mode_fw.fw_file;

	/* all 10.x firmware versions support thermal throttling but don't
	 * advertise the support via service flags so we have to hardcode
	 * it here
	 */
	switch (fw_file->wmi_op_version) {
	case ATH10K_FW_WMI_OP_VERSION_10_1:
	case ATH10K_FW_WMI_OP_VERSION_10_2:
	case ATH10K_FW_WMI_OP_VERSION_10_2_4:
	case ATH10K_FW_WMI_OP_VERSION_10_4:
		set_bit(WMI_SERVICE_THERM_THROT, ar->wmi.svc_map);
		break;
	default:
		break;
	}

	return 0;
}