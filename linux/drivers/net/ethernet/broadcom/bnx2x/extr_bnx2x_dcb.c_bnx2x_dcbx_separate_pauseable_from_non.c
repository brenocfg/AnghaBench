#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct dcbx_ets_feature {int /*<<< orphan*/  pg_bw_tbl; } ;
struct cos_help_data {TYPE_3__* data; } ;
struct TYPE_4__ {int* traffic_type_priority; } ;
struct TYPE_5__ {TYPE_1__ app; } ;
struct bnx2x {TYPE_2__ dcbx_port_params; } ;
struct TYPE_6__ {int pausable; int pri_join_mask; int /*<<< orphan*/  strict; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DCBX_STRICT_COS_HIGHEST ; 
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 size_t DCBX_MAX_NUM_PG_BW_ENTRIES ; 
 int DCBX_PFC_PRI_NON_PAUSE_MASK (struct bnx2x*) ; 
 int /*<<< orphan*/  DCBX_PG_BW_GET (int /*<<< orphan*/ ,size_t) ; 
 size_t LLFC_DRIVER_TRAFFIC_TYPE_MAX ; 
 int /*<<< orphan*/  bnx2x_dcbx_add_to_cos_bw (struct bnx2x*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_dcbx_separate_pauseable_from_non(struct bnx2x *bp,
			struct cos_help_data *cos_data,
			u32 *pg_pri_orginal_spread,
			struct dcbx_ets_feature *ets)
{
	u32	pri_tested	= 0;
	u8	i		= 0;
	u8	entry		= 0;
	u8	pg_entry	= 0;
	u8	num_of_pri	= LLFC_DRIVER_TRAFFIC_TYPE_MAX;

	cos_data->data[0].pausable = true;
	cos_data->data[1].pausable = false;
	cos_data->data[0].pri_join_mask = cos_data->data[1].pri_join_mask = 0;

	for (i = 0 ; i < num_of_pri ; i++) {
		pri_tested = 1 << bp->dcbx_port_params.
					app.traffic_type_priority[i];

		if (pri_tested & DCBX_PFC_PRI_NON_PAUSE_MASK(bp)) {
			cos_data->data[1].pri_join_mask |= pri_tested;
			entry = 1;
		} else {
			cos_data->data[0].pri_join_mask |= pri_tested;
			entry = 0;
		}
		pg_entry = (u8)pg_pri_orginal_spread[bp->dcbx_port_params.
						app.traffic_type_priority[i]];
		/* There can be only one strict pg */
		if (pg_entry < DCBX_MAX_NUM_PG_BW_ENTRIES)
			bnx2x_dcbx_add_to_cos_bw(bp, &cos_data->data[entry],
				DCBX_PG_BW_GET(ets->pg_bw_tbl, pg_entry));
		else
			/* If we join a group and one is strict
			 * than the bw rules
			 */
			cos_data->data[entry].strict =
						BNX2X_DCBX_STRICT_COS_HIGHEST;
	}
	if ((0 == cos_data->data[0].pri_join_mask) &&
	    (0 == cos_data->data[1].pri_join_mask))
		BNX2X_ERR("dcbx error: Both groups must have priorities\n");
}