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
union bfi_lps_i2h_msg_u {int /*<<< orphan*/  cvl_event; int /*<<< orphan*/  logout_rsp; int /*<<< orphan*/  login_rsp; struct bfi_msg_s* msg; } ;
struct TYPE_2__ {int msg_id; } ;
struct bfi_msg_s {TYPE_1__ mhdr; } ;
struct bfa_s {int dummy; } ;

/* Variables and functions */
#define  BFI_LPS_I2H_CVL_EVENT 130 
#define  BFI_LPS_I2H_LOGIN_RSP 129 
#define  BFI_LPS_I2H_LOGOUT_RSP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_lps_login_rsp (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_lps_logout_rsp (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_lps_rx_cvl_event (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int) ; 

void
bfa_lps_isr(struct bfa_s *bfa, struct bfi_msg_s *m)
{
	union bfi_lps_i2h_msg_u	msg;

	bfa_trc(bfa, m->mhdr.msg_id);
	msg.msg = m;

	switch (m->mhdr.msg_id) {
	case BFI_LPS_I2H_LOGIN_RSP:
		bfa_lps_login_rsp(bfa, msg.login_rsp);
		break;

	case BFI_LPS_I2H_LOGOUT_RSP:
		bfa_lps_logout_rsp(bfa, msg.logout_rsp);
		break;

	case BFI_LPS_I2H_CVL_EVENT:
		bfa_lps_rx_cvl_event(bfa, msg.cvl_event);
		break;

	default:
		bfa_trc(bfa, m->mhdr.msg_id);
		WARN_ON(1);
	}
}