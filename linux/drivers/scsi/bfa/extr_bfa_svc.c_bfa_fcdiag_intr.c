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
struct TYPE_2__ {int msg_id; } ;
struct bfi_msg_s {TYPE_1__ mhdr; } ;
struct bfi_diag_lb_rsp_s {int dummy; } ;
struct bfi_diag_dport_scn_s {int dummy; } ;
struct bfi_diag_dport_rsp_s {int dummy; } ;
struct bfa_s {int dummy; } ;
struct bfa_fcdiag_s {int /*<<< orphan*/  dport; } ;
typedef  int /*<<< orphan*/  bfi_diag_qtest_rsp_t ;

/* Variables and functions */
 struct bfa_fcdiag_s* BFA_FCDIAG_MOD (struct bfa_s*) ; 
#define  BFI_DIAG_I2H_DPORT 131 
#define  BFI_DIAG_I2H_DPORT_SCN 130 
#define  BFI_DIAG_I2H_LOOPBACK 129 
#define  BFI_DIAG_I2H_QTEST 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_dport_req_comp (int /*<<< orphan*/ *,struct bfi_diag_dport_rsp_s*) ; 
 int /*<<< orphan*/  bfa_dport_scn (int /*<<< orphan*/ *,struct bfi_diag_dport_scn_s*) ; 
 int /*<<< orphan*/  bfa_fcdiag_loopback_comp (struct bfa_fcdiag_s*,struct bfi_diag_lb_rsp_s*) ; 
 int /*<<< orphan*/  bfa_fcdiag_queuetest_comp (struct bfa_fcdiag_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_fcdiag_s*,int) ; 

void
bfa_fcdiag_intr(struct bfa_s *bfa, struct bfi_msg_s *msg)
{
	struct bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);

	switch (msg->mhdr.msg_id) {
	case BFI_DIAG_I2H_LOOPBACK:
		bfa_fcdiag_loopback_comp(fcdiag,
				(struct bfi_diag_lb_rsp_s *) msg);
		break;
	case BFI_DIAG_I2H_QTEST:
		bfa_fcdiag_queuetest_comp(fcdiag, (bfi_diag_qtest_rsp_t *)msg);
		break;
	case BFI_DIAG_I2H_DPORT:
		bfa_dport_req_comp(&fcdiag->dport,
				(struct bfi_diag_dport_rsp_s *)msg);
		break;
	case BFI_DIAG_I2H_DPORT_SCN:
		bfa_dport_scn(&fcdiag->dport,
				(struct bfi_diag_dport_scn_s *)msg);
		break;
	default:
		bfa_trc(fcdiag, msg->mhdr.msg_id);
		WARN_ON(1);
	}
}