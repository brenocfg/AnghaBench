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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_hba {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int lpfc_oas_lun_state_set (struct lpfc_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
lpfc_oas_lun_state_change(struct lpfc_hba *phba, uint8_t vpt_wwpn[],
			  uint8_t tgt_wwpn[], uint64_t lun,
			  uint32_t oas_state, uint8_t pri)
{

	int rc;

	rc = lpfc_oas_lun_state_set(phba, vpt_wwpn, tgt_wwpn, lun,
				    oas_state, pri);
	return rc;
}