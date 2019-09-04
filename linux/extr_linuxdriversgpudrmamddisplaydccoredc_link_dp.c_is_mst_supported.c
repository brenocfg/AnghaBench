#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int MST_CAP; } ;
union mstm_cap {scalar_t__ raw; TYPE_1__ bits; } ;
union dpcd_rev {scalar_t__ raw; } ;
struct dc_link {int dummy; } ;
typedef  int /*<<< orphan*/  rev ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
typedef  int /*<<< orphan*/  cap ;

/* Variables and functions */
 int DC_OK ; 
 scalar_t__ DPCD_REV_12 ; 
 int /*<<< orphan*/  DP_DPCD_REV ; 
 int /*<<< orphan*/  DP_MSTM_CAP ; 
 int core_link_read_dpcd (struct dc_link*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

bool is_mst_supported(struct dc_link *link)
{
	bool mst          = false;
	enum dc_status st = DC_OK;
	union dpcd_rev rev;
	union mstm_cap cap;

	rev.raw  = 0;
	cap.raw  = 0;

	st = core_link_read_dpcd(link, DP_DPCD_REV, &rev.raw,
			sizeof(rev));

	if (st == DC_OK && rev.raw >= DPCD_REV_12) {

		st = core_link_read_dpcd(link, DP_MSTM_CAP,
				&cap.raw, sizeof(cap));
		if (st == DC_OK && cap.bits.MST_CAP == 1)
			mst = true;
	}
	return mst;

}