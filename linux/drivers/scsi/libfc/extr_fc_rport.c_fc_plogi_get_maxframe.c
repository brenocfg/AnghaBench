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
struct TYPE_3__ {int /*<<< orphan*/  sp_bb_data; } ;
struct fc_els_flogi {TYPE_2__* fl_cssp; TYPE_1__ fl_csp; } ;
struct TYPE_4__ {int /*<<< orphan*/  cp_rdfs; } ;

/* Variables and functions */
 unsigned int FC_SP_BB_DATA_MASK ; 
 unsigned int FC_SP_MIN_MAX_PAYLOAD ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int fc_plogi_get_maxframe(struct fc_els_flogi *flp,
					  unsigned int maxval)
{
	unsigned int mfs;

	/*
	 * Get max payload from the common service parameters and the
	 * class 3 receive data field size.
	 */
	mfs = ntohs(flp->fl_csp.sp_bb_data) & FC_SP_BB_DATA_MASK;
	if (mfs >= FC_SP_MIN_MAX_PAYLOAD && mfs < maxval)
		maxval = mfs;
	mfs = ntohs(flp->fl_cssp[3 - 1].cp_rdfs);
	if (mfs >= FC_SP_MIN_MAX_PAYLOAD && mfs < maxval)
		maxval = mfs;
	return maxval;
}