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
typedef  int u32 ;
struct iwl_trans {int hw_rev; } ;

/* Variables and functions */
#define  CSR_HW_REV_TYPE_5100 132 
#define  CSR_HW_REV_TYPE_5150 131 
#define  CSR_HW_REV_TYPE_5300 130 
#define  CSR_HW_REV_TYPE_5350 129 
 int CSR_HW_REV_TYPE_MSK ; 
#define  CSR_HW_REV_TYPE_NONE 128 
 int /*<<< orphan*/  CSR_OTP_GP_REG ; 
 int CSR_OTP_GP_REG_DEVICE_SELECT ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*) ; 
 int iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_nvm_is_otp(struct iwl_trans *trans)
{
	u32 otpgp;

	/* OTP only valid for CP/PP and after */
	switch (trans->hw_rev & CSR_HW_REV_TYPE_MSK) {
	case CSR_HW_REV_TYPE_NONE:
		IWL_ERR(trans, "Unknown hardware type\n");
		return -EIO;
	case CSR_HW_REV_TYPE_5300:
	case CSR_HW_REV_TYPE_5350:
	case CSR_HW_REV_TYPE_5100:
	case CSR_HW_REV_TYPE_5150:
		return 0;
	default:
		otpgp = iwl_read32(trans, CSR_OTP_GP_REG);
		if (otpgp & CSR_OTP_GP_REG_DEVICE_SELECT)
			return 1;
		return 0;
	}
}