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
struct csio_hw {int evtflag; int prev_evt; int cur_evt; int /*<<< orphan*/  sm; } ;
typedef  enum csio_hw_ev { ____Placeholder_csio_hw_ev } csio_hw_ev ;

/* Variables and functions */
#define  CSIO_HWE_FATAL 133 
#define  CSIO_HWE_FW_DLOAD 132 
#define  CSIO_HWE_HBA_RESET 131 
#define  CSIO_HWE_PCIERR_DETECTED 130 
#define  CSIO_HWE_PCI_REMOVE 129 
 int /*<<< orphan*/  CSIO_HWE_QUIESCED ; 
#define  CSIO_HWE_SUSPEND 128 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_LN_NOTIFY_HWSTOP ; 
 int /*<<< orphan*/  csio_evtq_flush (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_evtq_stop (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_intr_disable (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_mbm_cleanup (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_to_mgmtm (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_to_scsim (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hws_quiescing ; 
 int /*<<< orphan*/  csio_hws_uninit ; 
 int /*<<< orphan*/  csio_mgmtm_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_notify_lnodes (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_scsim_cleanup_io (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csio_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * n_evt_sm ; 
 int /*<<< orphan*/  n_evt_unexp ; 

__attribute__((used)) static void
csio_hws_ready(struct csio_hw *hw, enum csio_hw_ev evt)
{
	/* Remember the event */
	hw->evtflag = evt;

	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	switch (evt) {
	case CSIO_HWE_HBA_RESET:
	case CSIO_HWE_FW_DLOAD:
	case CSIO_HWE_SUSPEND:
	case CSIO_HWE_PCI_REMOVE:
	case CSIO_HWE_PCIERR_DETECTED:
		csio_set_state(&hw->sm, csio_hws_quiescing);
		/* cleanup all outstanding cmds */
		if (evt == CSIO_HWE_HBA_RESET ||
		    evt == CSIO_HWE_PCIERR_DETECTED)
			csio_scsim_cleanup_io(csio_hw_to_scsim(hw), false);
		else
			csio_scsim_cleanup_io(csio_hw_to_scsim(hw), true);

		csio_hw_intr_disable(hw);
		csio_hw_mbm_cleanup(hw);
		csio_evtq_stop(hw);
		csio_notify_lnodes(hw, CSIO_LN_NOTIFY_HWSTOP);
		csio_evtq_flush(hw);
		csio_mgmtm_cleanup(csio_hw_to_mgmtm(hw));
		csio_post_event(&hw->sm, CSIO_HWE_QUIESCED);
		break;

	case CSIO_HWE_FATAL:
		csio_set_state(&hw->sm, csio_hws_uninit);
		break;

	default:
		CSIO_INC_STATS(hw, n_evt_unexp);
		break;
	}
}