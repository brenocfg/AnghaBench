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
union bfi_iocfc_i2h_msg_u {TYPE_1__ mh; } ;
struct bfi_mbmsg_s {int dummy; } ;
struct bfi_faa_addr_msg_s {int dummy; } ;
struct bfa_iocfc_s {int /*<<< orphan*/  updateq_cbarg; int /*<<< orphan*/  (* updateq_cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct bfa_s {struct bfa_iocfc_s iocfc; } ;
typedef  int /*<<< orphan*/  bfi_faa_query_rsp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_OK ; 
#define  BFI_IOCFC_I2H_ADDR_MSG 131 
#define  BFI_IOCFC_I2H_CFG_REPLY 130 
#define  BFI_IOCFC_I2H_FAA_QUERY_RSP 129 
#define  BFI_IOCFC_I2H_UPDATEQ_RSP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_faa_query_reply (struct bfa_iocfc_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_iocfc_cfgrsp (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_iocfc_process_faa_addr (struct bfa_s*,struct bfi_faa_addr_msg_s*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_iocfc_isr(void *bfaarg, struct bfi_mbmsg_s *m)
{
	struct bfa_s		*bfa = bfaarg;
	struct bfa_iocfc_s	*iocfc = &bfa->iocfc;
	union bfi_iocfc_i2h_msg_u	*msg;

	msg = (union bfi_iocfc_i2h_msg_u *) m;
	bfa_trc(bfa, msg->mh.msg_id);

	switch (msg->mh.msg_id) {
	case BFI_IOCFC_I2H_CFG_REPLY:
		bfa_iocfc_cfgrsp(bfa);
		break;
	case BFI_IOCFC_I2H_UPDATEQ_RSP:
		iocfc->updateq_cbfn(iocfc->updateq_cbarg, BFA_STATUS_OK);
		break;
	case BFI_IOCFC_I2H_ADDR_MSG:
		bfa_iocfc_process_faa_addr(bfa,
				(struct bfi_faa_addr_msg_s *)msg);
		break;
	case BFI_IOCFC_I2H_FAA_QUERY_RSP:
		bfa_faa_query_reply(iocfc, (bfi_faa_query_rsp_t *)msg);
		break;
	default:
		WARN_ON(1);
	}
}