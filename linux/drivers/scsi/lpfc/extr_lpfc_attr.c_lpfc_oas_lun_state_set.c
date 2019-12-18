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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct lpfc_name {int dummy; } ;
struct lpfc_hba {int /*<<< orphan*/  cfg_fof; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t EPERM ; 
 int /*<<< orphan*/  lpfc_disable_oas_lun (struct lpfc_hba*,struct lpfc_name*,struct lpfc_name*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_oas_lun (struct lpfc_hba*,struct lpfc_name*,struct lpfc_name*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
lpfc_oas_lun_state_set(struct lpfc_hba *phba, uint8_t vpt_wwpn[],
		       uint8_t tgt_wwpn[], uint64_t lun,
		       uint32_t oas_state, uint8_t pri)
{

	int rc = 0;

	if (!phba->cfg_fof)
		return -EPERM;

	if (oas_state) {
		if (!lpfc_enable_oas_lun(phba, (struct lpfc_name *)vpt_wwpn,
					 (struct lpfc_name *)tgt_wwpn,
					 lun, pri))
			rc = -ENOMEM;
	} else {
		lpfc_disable_oas_lun(phba, (struct lpfc_name *)vpt_wwpn,
				     (struct lpfc_name *)tgt_wwpn, lun, pri);
	}
	return rc;

}