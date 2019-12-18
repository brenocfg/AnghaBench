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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_6__ {TYPE_1__ mac; } ;
struct i40e_pf {TYPE_2__* pdev; int /*<<< orphan*/  state; TYPE_3__ hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_GL_FWSTS ; 
 scalar_t__ I40E_GL_FWSTS_FWS1B_MASK ; 
 scalar_t__ I40E_MAC_X722 ; 
 scalar_t__ I40E_MAC_XL710 ; 
 scalar_t__ I40E_X722_GL_FWSTS_FWS1B_REC_MOD_CORER_MASK ; 
 scalar_t__ I40E_X722_GL_FWSTS_FWS1B_REC_MOD_GLOBR_MASK ; 
 scalar_t__ I40E_XL710_GL_FWSTS_FWS1B_REC_MOD_CORER_MASK ; 
 scalar_t__ I40E_XL710_GL_FWSTS_FWS1B_REC_MOD_GLOBR_MASK ; 
 scalar_t__ I40E_XL710_GL_FWSTS_FWS1B_REC_MOD_NVM_MASK ; 
 scalar_t__ I40E_XL710_GL_FWSTS_FWS1B_REC_MOD_TRANSITION_MASK ; 
 int /*<<< orphan*/  __I40E_RECOVERY_MODE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ rd32 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i40e_check_recovery_mode(struct i40e_pf *pf)
{
	u32 val = rd32(&pf->hw, I40E_GL_FWSTS) & I40E_GL_FWSTS_FWS1B_MASK;
	bool is_recovery_mode = false;

	if (pf->hw.mac.type == I40E_MAC_XL710)
		is_recovery_mode =
		val == I40E_XL710_GL_FWSTS_FWS1B_REC_MOD_CORER_MASK ||
		val == I40E_XL710_GL_FWSTS_FWS1B_REC_MOD_GLOBR_MASK ||
		val == I40E_XL710_GL_FWSTS_FWS1B_REC_MOD_TRANSITION_MASK ||
		val == I40E_XL710_GL_FWSTS_FWS1B_REC_MOD_NVM_MASK;
	if (pf->hw.mac.type == I40E_MAC_X722)
		is_recovery_mode =
		val == I40E_X722_GL_FWSTS_FWS1B_REC_MOD_CORER_MASK ||
		val == I40E_X722_GL_FWSTS_FWS1B_REC_MOD_GLOBR_MASK;
	if (is_recovery_mode) {
		dev_notice(&pf->pdev->dev, "Firmware recovery mode detected. Limiting functionality.\n");
		dev_notice(&pf->pdev->dev, "Refer to the Intel(R) Ethernet Adapters and Devices User Guide for details on firmware recovery mode.\n");
		set_bit(__I40E_RECOVERY_MODE, pf->state);

		return true;
	}
	if (test_and_clear_bit(__I40E_RECOVERY_MODE, pf->state))
		dev_info(&pf->pdev->dev, "Reinitializing in normal mode with full functionality.\n");

	return false;
}