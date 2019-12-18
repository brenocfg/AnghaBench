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
typedef  int /*<<< orphan*/  uint16_t ;
struct se_cmd {int prot_checks; } ;
struct qla_tgt_cmd {struct se_cmd se_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PO_DISABLE_GUARD_CHECK ; 
 int /*<<< orphan*/  PO_DIS_APP_TAG_VALD ; 
 int TARGET_DIF_CHECK_APPTAG ; 
 int TARGET_DIF_CHECK_GUARD ; 

__attribute__((used)) static int tcm_qla2xxx_dif_tags(struct qla_tgt_cmd *cmd,
    uint16_t *pfw_prot_opts)
{
	struct se_cmd *se_cmd = &cmd->se_cmd;

	if (!(se_cmd->prot_checks & TARGET_DIF_CHECK_GUARD))
		*pfw_prot_opts |= PO_DISABLE_GUARD_CHECK;

	if (!(se_cmd->prot_checks & TARGET_DIF_CHECK_APPTAG))
		*pfw_prot_opts |= PO_DIS_APP_TAG_VALD;

	return 0;
}