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
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  csio_evtq_cleanup (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_to_mbm (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_to_mgmtm (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_to_scsim (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_to_wrm (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_mbm_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_mgmtm_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_scsim_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_wrm_exit (int /*<<< orphan*/ ,struct csio_hw*) ; 

void
csio_hw_exit(struct csio_hw *hw)
{
	csio_evtq_cleanup(hw);
	csio_mgmtm_exit(csio_hw_to_mgmtm(hw));
	csio_scsim_exit(csio_hw_to_scsim(hw));
	csio_wrm_exit(csio_hw_to_wrm(hw), hw);
	csio_mbm_exit(csio_hw_to_mbm(hw));
}