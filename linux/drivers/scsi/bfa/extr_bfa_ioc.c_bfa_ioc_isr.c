#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int msg_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  cap_bm; int /*<<< orphan*/  port_mode; } ;
union bfi_ioc_i2h_msg_u {TYPE_2__ mh; TYPE_1__ fw_event; } ;
struct bfi_mbmsg_s {int dummy; } ;
struct bfa_iocpf_s {int dummy; } ;
struct bfa_ioc_s {int port_mode; int port_mode_cfg; int /*<<< orphan*/  ad_cap_bm; struct bfa_iocpf_s iocpf; } ;
typedef  enum bfa_mode_s { ____Placeholder_bfa_mode_s } bfa_mode_s ;

/* Variables and functions */
#define  BFI_IOC_I2H_DISABLE_REPLY 131 
#define  BFI_IOC_I2H_ENABLE_REPLY 130 
#define  BFI_IOC_I2H_GETATTR_REPLY 129 
#define  BFI_IOC_I2H_HBEAT 128 
 int /*<<< orphan*/  IOCPF_E_FWRSP_DISABLE ; 
 int /*<<< orphan*/  IOCPF_E_FWRSP_ENABLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bfa_iocpf_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_getattr_reply (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_stats (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,int) ; 
 int /*<<< orphan*/  ioc_isrs ; 

void
bfa_ioc_isr(struct bfa_ioc_s *ioc, struct bfi_mbmsg_s *m)
{
	union bfi_ioc_i2h_msg_u	*msg;
	struct bfa_iocpf_s *iocpf = &ioc->iocpf;

	msg = (union bfi_ioc_i2h_msg_u *) m;

	bfa_ioc_stats(ioc, ioc_isrs);

	switch (msg->mh.msg_id) {
	case BFI_IOC_I2H_HBEAT:
		break;

	case BFI_IOC_I2H_ENABLE_REPLY:
		ioc->port_mode = ioc->port_mode_cfg =
				(enum bfa_mode_s)msg->fw_event.port_mode;
		ioc->ad_cap_bm = msg->fw_event.cap_bm;
		bfa_fsm_send_event(iocpf, IOCPF_E_FWRSP_ENABLE);
		break;

	case BFI_IOC_I2H_DISABLE_REPLY:
		bfa_fsm_send_event(iocpf, IOCPF_E_FWRSP_DISABLE);
		break;

	case BFI_IOC_I2H_GETATTR_REPLY:
		bfa_ioc_getattr_reply(ioc);
		break;

	default:
		bfa_trc(ioc, msg->mh.msg_id);
		WARN_ON(1);
	}
}