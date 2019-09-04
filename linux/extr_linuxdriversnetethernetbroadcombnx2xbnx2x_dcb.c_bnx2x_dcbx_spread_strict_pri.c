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
typedef  int u8 ;
struct cos_help_data {struct cos_entry_help_data* data; } ;
struct cos_entry_help_data {int strict; int pri_join_mask; void* pausable; void* cos_bw; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_DCBX_STRICT_COS_HIGHEST ; 
 int BNX2X_DCBX_STRICT_COS_NEXT_LOWER_PRI (int) ; 
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 void* DCBX_INVALID_COS_BW ; 
 void* DCBX_IS_PFC_PRI_SOME_PAUSE (struct bnx2x*,int) ; 
 int EINVAL ; 
 int MAX_PFC_PRIORITIES ; 

__attribute__((used)) static int bnx2x_dcbx_spread_strict_pri(struct bnx2x *bp,
					struct cos_help_data *cos_data,
					u8 entry,
					u8 num_spread_of_entries,
					u8 strict_app_pris)
{
	u8 strict_pri = BNX2X_DCBX_STRICT_COS_HIGHEST;
	u8 num_of_app_pri = MAX_PFC_PRIORITIES;
	u8 app_pri_bit = 0;

	while (num_spread_of_entries && num_of_app_pri > 0) {
		app_pri_bit = 1 << (num_of_app_pri - 1);
		if (app_pri_bit & strict_app_pris) {
			struct cos_entry_help_data *data = &cos_data->
								data[entry];
			num_spread_of_entries--;
			if (num_spread_of_entries == 0) {
				/* last entry needed put all the entries left */
				data->cos_bw = DCBX_INVALID_COS_BW;
				data->strict = strict_pri;
				data->pri_join_mask = strict_app_pris;
				data->pausable = DCBX_IS_PFC_PRI_SOME_PAUSE(bp,
							data->pri_join_mask);
			} else {
				strict_app_pris &= ~app_pri_bit;

				data->cos_bw = DCBX_INVALID_COS_BW;
				data->strict = strict_pri;
				data->pri_join_mask = app_pri_bit;
				data->pausable = DCBX_IS_PFC_PRI_SOME_PAUSE(bp,
							data->pri_join_mask);
			}

			strict_pri =
			    BNX2X_DCBX_STRICT_COS_NEXT_LOWER_PRI(strict_pri);
			entry++;
		}

		num_of_app_pri--;
	}

	if (num_spread_of_entries) {
		BNX2X_ERR("Didn't succeed to spread strict priorities\n");
		return -EINVAL;
	}

	return 0;
}