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
struct csio_hw {int prev_evt; int cur_evt; } ;
typedef  enum csio_hw_ev { ____Placeholder_csio_hw_ev } csio_hw_ev ;

/* Variables and functions */
#define  CSIO_HWE_HBA_RESET 128 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int PIORSTMODE_F ; 
 int PIORST_F ; 
 int /*<<< orphan*/  PL_RST_A ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*) ; 
 int /*<<< orphan*/  csio_is_hw_master (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/ * n_evt_sm ; 
 int /*<<< orphan*/  n_evt_unexp ; 

__attribute__((used)) static void
csio_hws_removing(struct csio_hw *hw, enum csio_hw_ev evt)
{
	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	switch (evt) {
	case CSIO_HWE_HBA_RESET:
		if (!csio_is_hw_master(hw))
			break;
		/*
		 * The BYE should have alerady been issued, so we cant
		 * use the mailbox interface. Hence we use the PL_RST
		 * register directly.
		 */
		csio_err(hw, "Resetting HW and waiting 2 seconds...\n");
		csio_wr_reg32(hw, PIORSTMODE_F | PIORST_F, PL_RST_A);
		mdelay(2000);
		break;

	/* Should never receive any new events */
	default:
		CSIO_INC_STATS(hw, n_evt_unexp);
		break;

	}
}