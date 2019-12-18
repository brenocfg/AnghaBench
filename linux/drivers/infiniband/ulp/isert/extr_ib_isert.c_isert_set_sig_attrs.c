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
struct se_cmd {int prot_op; int prot_checks; } ;
struct TYPE_2__ {void* sig_type; } ;
struct ib_sig_attrs {int /*<<< orphan*/  check_mask; TYPE_1__ mem; TYPE_1__ wire; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_SIG_CHECK_APPTAG ; 
 int /*<<< orphan*/  IB_SIG_CHECK_GUARD ; 
 int /*<<< orphan*/  IB_SIG_CHECK_REFTAG ; 
 void* IB_SIG_TYPE_NONE ; 
 int TARGET_DIF_CHECK_APPTAG ; 
 int TARGET_DIF_CHECK_GUARD ; 
 int TARGET_DIF_CHECK_REFTAG ; 
#define  TARGET_PROT_DIN_INSERT 133 
#define  TARGET_PROT_DIN_PASS 132 
#define  TARGET_PROT_DIN_STRIP 131 
#define  TARGET_PROT_DOUT_INSERT 130 
#define  TARGET_PROT_DOUT_PASS 129 
#define  TARGET_PROT_DOUT_STRIP 128 
 int /*<<< orphan*/  isert_err (char*,int) ; 
 int /*<<< orphan*/  isert_set_dif_domain (struct se_cmd*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct ib_sig_attrs*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
isert_set_sig_attrs(struct se_cmd *se_cmd, struct ib_sig_attrs *sig_attrs)
{
	memset(sig_attrs, 0, sizeof(*sig_attrs));

	switch (se_cmd->prot_op) {
	case TARGET_PROT_DIN_INSERT:
	case TARGET_PROT_DOUT_STRIP:
		sig_attrs->mem.sig_type = IB_SIG_TYPE_NONE;
		isert_set_dif_domain(se_cmd, &sig_attrs->wire);
		break;
	case TARGET_PROT_DOUT_INSERT:
	case TARGET_PROT_DIN_STRIP:
		sig_attrs->wire.sig_type = IB_SIG_TYPE_NONE;
		isert_set_dif_domain(se_cmd, &sig_attrs->mem);
		break;
	case TARGET_PROT_DIN_PASS:
	case TARGET_PROT_DOUT_PASS:
		isert_set_dif_domain(se_cmd, &sig_attrs->wire);
		isert_set_dif_domain(se_cmd, &sig_attrs->mem);
		break;
	default:
		isert_err("Unsupported PI operation %d\n", se_cmd->prot_op);
		return -EINVAL;
	}

	if (se_cmd->prot_checks & TARGET_DIF_CHECK_GUARD)
		sig_attrs->check_mask |= IB_SIG_CHECK_GUARD;
	if (se_cmd->prot_checks & TARGET_DIF_CHECK_APPTAG)
		sig_attrs->check_mask |= IB_SIG_CHECK_APPTAG;
	if (se_cmd->prot_checks & TARGET_DIF_CHECK_REFTAG)
		sig_attrs->check_mask |= IB_SIG_CHECK_REFTAG;

	return 0;
}