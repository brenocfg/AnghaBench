#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfad_s {int dummy; } ;
struct bfa_fcport_s {TYPE_1__* bfa; int /*<<< orphan*/  pwwn; } ;
typedef  enum bfa_fcport_sm_event { ____Placeholder_bfa_fcport_sm_event } bfa_fcport_sm_event ;
struct TYPE_4__ {int /*<<< orphan*/  plog; scalar_t__ bfad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
#define  BFA_FCPORT_SM_DISABLE 133 
#define  BFA_FCPORT_SM_ENABLE 132 
#define  BFA_FCPORT_SM_FAA_MISCONFIG 131 
#define  BFA_FCPORT_SM_HWFAIL 130 
#define  BFA_FCPORT_SM_LINKDOWN 129 
#define  BFA_FCPORT_SM_STOP 128 
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  BFA_PL_EID_PORT_DISABLE ; 
 int /*<<< orphan*/  BFA_PL_EID_PORT_ST_CHANGE ; 
 int /*<<< orphan*/  BFA_PL_MID_HAL ; 
 int /*<<< orphan*/  BFA_PORT_AEN_DISABLE ; 
 int /*<<< orphan*/  BFA_PORT_AEN_DISCONNECT ; 
 int /*<<< orphan*/  BFA_PORT_AEN_OFFLINE ; 
 int /*<<< orphan*/  BFA_PORT_IS_DISABLED (TYPE_1__*) ; 
 int /*<<< orphan*/  BFA_PORT_LINKDOWN ; 
 int BFA_STRING_32 ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  bfa_fcport_aen_post (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcport_reset_linkinfo (struct bfa_fcport_s*) ; 
 int /*<<< orphan*/  bfa_fcport_scn (struct bfa_fcport_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcport_send_disable (struct bfa_fcport_s*) ; 
 int /*<<< orphan*/  bfa_fcport_sm_disabling ; 
 int /*<<< orphan*/  bfa_fcport_sm_disabling_qwait ; 
 int /*<<< orphan*/  bfa_fcport_sm_faa_misconfig ; 
 int /*<<< orphan*/  bfa_fcport_sm_iocdown ; 
 int /*<<< orphan*/  bfa_fcport_sm_linkdown ; 
 int /*<<< orphan*/  bfa_fcport_sm_stopped ; 
 int /*<<< orphan*/  bfa_log_level ; 
 int /*<<< orphan*/  bfa_plog_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wwn2str (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcport_sm_linkup(struct bfa_fcport_s *fcport,
	enum bfa_fcport_sm_event event)
{
	char pwwn_buf[BFA_STRING_32];
	struct bfad_s *bfad = (struct bfad_s *)fcport->bfa->bfad;

	bfa_trc(fcport->bfa, event);

	switch (event) {
	case BFA_FCPORT_SM_ENABLE:
		/*
		 * Already enabled.
		 */
		break;

	case BFA_FCPORT_SM_DISABLE:
		if (bfa_fcport_send_disable(fcport))
			bfa_sm_set_state(fcport, bfa_fcport_sm_disabling);
		else
			bfa_sm_set_state(fcport,
					 bfa_fcport_sm_disabling_qwait);

		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_scn(fcport, BFA_PORT_LINKDOWN, BFA_FALSE);
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
				BFA_PL_EID_PORT_DISABLE, 0, "Port Disable");
		wwn2str(pwwn_buf, fcport->pwwn);
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
			"Base port offline: WWN = %s\n", pwwn_buf);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_OFFLINE);
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
			"Base port disabled: WWN = %s\n", pwwn_buf);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISABLE);
		break;

	case BFA_FCPORT_SM_LINKDOWN:
		bfa_sm_set_state(fcport, bfa_fcport_sm_linkdown);
		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_scn(fcport, BFA_PORT_LINKDOWN, BFA_FALSE);
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
				BFA_PL_EID_PORT_ST_CHANGE, 0, "Port Linkdown");
		wwn2str(pwwn_buf, fcport->pwwn);
		if (BFA_PORT_IS_DISABLED(fcport->bfa)) {
			BFA_LOG(KERN_INFO, bfad, bfa_log_level,
				"Base port offline: WWN = %s\n", pwwn_buf);
			bfa_fcport_aen_post(fcport, BFA_PORT_AEN_OFFLINE);
		} else {
			BFA_LOG(KERN_ERR, bfad, bfa_log_level,
				"Base port (WWN = %s) "
				"lost fabric connectivity\n", pwwn_buf);
			bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISCONNECT);
		}
		break;

	case BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		bfa_fcport_reset_linkinfo(fcport);
		wwn2str(pwwn_buf, fcport->pwwn);
		if (BFA_PORT_IS_DISABLED(fcport->bfa)) {
			BFA_LOG(KERN_INFO, bfad, bfa_log_level,
				"Base port offline: WWN = %s\n", pwwn_buf);
			bfa_fcport_aen_post(fcport, BFA_PORT_AEN_OFFLINE);
		} else {
			BFA_LOG(KERN_ERR, bfad, bfa_log_level,
				"Base port (WWN = %s) "
				"lost fabric connectivity\n", pwwn_buf);
			bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISCONNECT);
		}
		break;

	case BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocdown);
		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_scn(fcport, BFA_PORT_LINKDOWN, BFA_FALSE);
		wwn2str(pwwn_buf, fcport->pwwn);
		if (BFA_PORT_IS_DISABLED(fcport->bfa)) {
			BFA_LOG(KERN_INFO, bfad, bfa_log_level,
				"Base port offline: WWN = %s\n", pwwn_buf);
			bfa_fcport_aen_post(fcport, BFA_PORT_AEN_OFFLINE);
		} else {
			BFA_LOG(KERN_ERR, bfad, bfa_log_level,
				"Base port (WWN = %s) "
				"lost fabric connectivity\n", pwwn_buf);
			bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISCONNECT);
		}
		break;

	case BFA_FCPORT_SM_FAA_MISCONFIG:
		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISCONNECT);
		bfa_sm_set_state(fcport, bfa_fcport_sm_faa_misconfig);
		break;

	default:
		bfa_sm_fault(fcport->bfa, event);
	}
}