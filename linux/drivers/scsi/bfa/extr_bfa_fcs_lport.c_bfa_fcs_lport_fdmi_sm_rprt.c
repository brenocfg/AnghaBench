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
struct TYPE_3__ {int pwwn; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  fcs; TYPE_1__ port_cfg; } ;
struct bfa_fcs_lport_fdmi_s {int /*<<< orphan*/  fcxp; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  timer; TYPE_2__* ms; } ;
typedef  enum port_fdmi_event { ____Placeholder_port_fdmi_event } port_fdmi_event ;
struct TYPE_4__ {struct bfa_fcs_lport_s* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_FDMI_CMD_MAX_RETRIES ; 
 int /*<<< orphan*/  BFA_FCS_GET_HAL_FROM_PORT (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  BFA_FCS_RETRY_TIMEOUT ; 
#define  FDMISM_EVENT_PORT_OFFLINE 130 
#define  FDMISM_EVENT_RSP_ERROR 129 
#define  FDMISM_EVENT_RSP_OK 128 
 int /*<<< orphan*/  bfa_fcs_lport_fdmi_sm_offline ; 
 int /*<<< orphan*/  bfa_fcs_lport_fdmi_sm_online ; 
 int /*<<< orphan*/  bfa_fcs_lport_fdmi_sm_rprt_retry ; 
 int /*<<< orphan*/  bfa_fcs_lport_fdmi_timeout ; 
 int /*<<< orphan*/  bfa_fcxp_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_lport_fdmi_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_fcs_lport_fdmi_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_lport_fdmi_sm_rprt(struct bfa_fcs_lport_fdmi_s *fdmi,
			enum port_fdmi_event event)
{
	struct bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	switch (event) {
	case FDMISM_EVENT_RSP_ERROR:
		/*
		 * if max retries have not been reached, start timer for a
		 * delayed retry
		 */
		if (fdmi->retry_cnt++ < BFA_FCS_FDMI_CMD_MAX_RETRIES) {
			bfa_sm_set_state(fdmi,
					bfa_fcs_lport_fdmi_sm_rprt_retry);
			bfa_timer_start(BFA_FCS_GET_HAL_FROM_PORT(port),
					    &fdmi->timer,
					    bfa_fcs_lport_fdmi_timeout, fdmi,
					    BFA_FCS_RETRY_TIMEOUT);

		} else {
			/*
			 * set state to offline
			 */
			bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
			fdmi->retry_cnt = 0;
		}
		break;

	case FDMISM_EVENT_RSP_OK:
		fdmi->retry_cnt = 0;
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_online);
		break;

	case FDMISM_EVENT_PORT_OFFLINE:
		bfa_fcxp_discard(fdmi->fcxp);
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
		break;

	default:
		bfa_sm_fault(port->fcs, event);
	}
}