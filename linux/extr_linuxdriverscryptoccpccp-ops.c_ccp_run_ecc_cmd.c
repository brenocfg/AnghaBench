#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ccp_ecc_engine {scalar_t__ mod_len; int function; int /*<<< orphan*/  mod; scalar_t__ ecc_result; } ;
struct ccp_cmd_queue {int dummy; } ;
struct TYPE_2__ {struct ccp_ecc_engine ecc; } ;
struct ccp_cmd {TYPE_1__ u; } ;

/* Variables and functions */
#define  CCP_ECC_FUNCTION_MADD_384BIT 133 
#define  CCP_ECC_FUNCTION_MINV_384BIT 132 
#define  CCP_ECC_FUNCTION_MMUL_384BIT 131 
#define  CCP_ECC_FUNCTION_PADD_384BIT 130 
#define  CCP_ECC_FUNCTION_PDBL_384BIT 129 
#define  CCP_ECC_FUNCTION_PMUL_384BIT 128 
 scalar_t__ CCP_ECC_MODULUS_BYTES ; 
 int EINVAL ; 
 int ccp_run_ecc_mm_cmd (struct ccp_cmd_queue*,struct ccp_cmd*) ; 
 int ccp_run_ecc_pm_cmd (struct ccp_cmd_queue*,struct ccp_cmd*) ; 

__attribute__((used)) static int ccp_run_ecc_cmd(struct ccp_cmd_queue *cmd_q, struct ccp_cmd *cmd)
{
	struct ccp_ecc_engine *ecc = &cmd->u.ecc;

	ecc->ecc_result = 0;

	if (!ecc->mod ||
	    (ecc->mod_len > CCP_ECC_MODULUS_BYTES))
		return -EINVAL;

	switch (ecc->function) {
	case CCP_ECC_FUNCTION_MMUL_384BIT:
	case CCP_ECC_FUNCTION_MADD_384BIT:
	case CCP_ECC_FUNCTION_MINV_384BIT:
		return ccp_run_ecc_mm_cmd(cmd_q, cmd);

	case CCP_ECC_FUNCTION_PADD_384BIT:
	case CCP_ECC_FUNCTION_PMUL_384BIT:
	case CCP_ECC_FUNCTION_PDBL_384BIT:
		return ccp_run_ecc_pm_cmd(cmd_q, cmd);

	default:
		return -EINVAL;
	}
}