#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfad_s {int dummy; } ;
struct bfa_fcport_s {TYPE_1__* bfa; int /*<<< orphan*/  pwwn; } ;
typedef  enum bfa_fcport_sm_event { ____Placeholder_bfa_fcport_sm_event } bfa_fcport_sm_event ;
struct TYPE_3__ {int /*<<< orphan*/  plog; scalar_t__ bfad; } ;

/* Variables and functions */
#define  BFA_FCPORT_SM_DDPORTENABLE 134 
#define  BFA_FCPORT_SM_DISABLE 133 
#define  BFA_FCPORT_SM_DPORTENABLE 132 
#define  BFA_FCPORT_SM_ENABLE 131 
#define  BFA_FCPORT_SM_HWFAIL 130 
#define  BFA_FCPORT_SM_START 129 
#define  BFA_FCPORT_SM_STOP 128 
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  BFA_PL_EID_PORT_ENABLE ; 
 int /*<<< orphan*/  BFA_PL_MID_HAL ; 
 int /*<<< orphan*/  BFA_PORT_AEN_ENABLE ; 
 int BFA_STRING_32 ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  bfa_fcport_aen_post (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcport_send_enable (struct bfa_fcport_s*) ; 
 int /*<<< orphan*/  bfa_fcport_sm_ddport ; 
 int /*<<< orphan*/  bfa_fcport_sm_dport ; 
 int /*<<< orphan*/  bfa_fcport_sm_enabling ; 
 int /*<<< orphan*/  bfa_fcport_sm_enabling_qwait ; 
 int /*<<< orphan*/  bfa_fcport_sm_iocfail ; 
 int /*<<< orphan*/  bfa_fcport_sm_stopped ; 
 int /*<<< orphan*/  bfa_log_level ; 
 int /*<<< orphan*/  bfa_plog_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wwn2str (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcport_sm_disabled(struct bfa_fcport_s *fcport,
						enum bfa_fcport_sm_event event)
{
	char pwwn_buf[BFA_STRING_32];
	struct bfad_s *bfad = (struct bfad_s *)fcport->bfa->bfad;
	bfa_trc(fcport->bfa, event);

	switch (event) {
	case BFA_FCPORT_SM_START:
		/*
		 * Ignore start event for a port that is disabled.
		 */
		break;

	case BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		break;

	case BFA_FCPORT_SM_ENABLE:
		if (bfa_fcport_send_enable(fcport))
			bfa_sm_set_state(fcport, bfa_fcport_sm_enabling);
		else
			bfa_sm_set_state(fcport,
					 bfa_fcport_sm_enabling_qwait);

		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
				BFA_PL_EID_PORT_ENABLE, 0, "Port Enable");
		wwn2str(pwwn_buf, fcport->pwwn);
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
			"Base port enabled: WWN = %s\n", pwwn_buf);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_ENABLE);
		break;

	case BFA_FCPORT_SM_DISABLE:
		/*
		 * Already disabled.
		 */
		break;

	case BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocfail);
		break;

	case BFA_FCPORT_SM_DPORTENABLE:
		bfa_sm_set_state(fcport, bfa_fcport_sm_dport);
		break;

	case BFA_FCPORT_SM_DDPORTENABLE:
		bfa_sm_set_state(fcport, bfa_fcport_sm_ddport);
		break;

	default:
		bfa_sm_fault(fcport->bfa, event);
	}
}