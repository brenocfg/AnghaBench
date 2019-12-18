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
struct csio_hw {int /*<<< orphan*/  fwevt_iq_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ CSIO_MAX_QID ; 
 int EINVAL ; 
 int /*<<< orphan*/  csio_process_fwevtq_entry ; 
 scalar_t__ csio_q_iqid (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int csio_wr_process_iq_idx (struct csio_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_int_stray ; 

int
csio_fwevtq_handler(struct csio_hw *hw)
{
	int rv;

	if (csio_q_iqid(hw, hw->fwevt_iq_idx) == CSIO_MAX_QID) {
		CSIO_INC_STATS(hw, n_int_stray);
		return -EINVAL;
	}

	rv = csio_wr_process_iq_idx(hw, hw->fwevt_iq_idx,
			   csio_process_fwevtq_entry, NULL);
	return rv;
}