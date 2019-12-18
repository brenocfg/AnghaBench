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
struct bfad_s {int /*<<< orphan*/  hal_tmo; } ;
typedef  enum bfad_sm_event { ____Placeholder_bfad_sm_event } bfad_sm_event ;

/* Variables and functions */
#define  BFAD_E_EXIT_COMP 130 
 int /*<<< orphan*/  BFAD_E_FCS_EXIT_COMP ; 
#define  BFAD_E_INIT_SUCCESS 129 
#define  BFAD_E_STOP 128 
 int BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_sm_fault (struct bfad_s*,int) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,int) ; 
 int /*<<< orphan*/  bfad_remove_intr (struct bfad_s*) ; 
 int /*<<< orphan*/  bfad_sm_fcs_exit ; 
 int /*<<< orphan*/  bfad_sm_operational ; 
 int /*<<< orphan*/  bfad_sm_uninit ; 
 int bfad_start_ops (struct bfad_s*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfad_sm_failed(struct bfad_s *bfad, enum bfad_sm_event event)
{
	int	retval;

	bfa_trc(bfad, event);

	switch (event) {
	case BFAD_E_INIT_SUCCESS:
		retval = bfad_start_ops(bfad);
		if (retval != BFA_STATUS_OK)
			break;
		bfa_sm_set_state(bfad, bfad_sm_operational);
		break;

	case BFAD_E_STOP:
		bfa_sm_set_state(bfad, bfad_sm_fcs_exit);
		bfa_sm_send_event(bfad, BFAD_E_FCS_EXIT_COMP);
		break;

	case BFAD_E_EXIT_COMP:
		bfa_sm_set_state(bfad, bfad_sm_uninit);
		bfad_remove_intr(bfad);
		del_timer_sync(&bfad->hal_tmo);
		break;

	default:
		bfa_sm_fault(bfad, event);
	}
}