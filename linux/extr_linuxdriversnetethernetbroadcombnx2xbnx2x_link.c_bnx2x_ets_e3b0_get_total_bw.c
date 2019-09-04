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
typedef  int u16 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_ets_params {size_t num_of_cos; TYPE_3__* cos; } ;
struct bnx2x {int dummy; } ;
struct TYPE_4__ {int bw; } ;
struct TYPE_5__ {TYPE_1__ bw_params; } ;
struct TYPE_6__ {scalar_t__ state; TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ bnx2x_cos_state_bw ; 

__attribute__((used)) static int bnx2x_ets_e3b0_get_total_bw(
	const struct link_params *params,
	struct bnx2x_ets_params *ets_params,
	u16 *total_bw)
{
	struct bnx2x *bp = params->bp;
	u8 cos_idx = 0;
	u8 is_bw_cos_exist = 0;

	*total_bw = 0 ;
	/* Calculate total BW requested */
	for (cos_idx = 0; cos_idx < ets_params->num_of_cos; cos_idx++) {
		if (ets_params->cos[cos_idx].state == bnx2x_cos_state_bw) {
			is_bw_cos_exist = 1;
			if (!ets_params->cos[cos_idx].params.bw_params.bw) {
				DP(NETIF_MSG_LINK, "bnx2x_ets_E3B0_config BW"
						   "was set to 0\n");
				/* This is to prevent a state when ramrods
				 * can't be sent
				 */
				ets_params->cos[cos_idx].params.bw_params.bw
					 = 1;
			}
			*total_bw +=
				ets_params->cos[cos_idx].params.bw_params.bw;
		}
	}

	/* Check total BW is valid */
	if ((is_bw_cos_exist == 1) && (*total_bw != 100)) {
		if (*total_bw == 0) {
			DP(NETIF_MSG_LINK,
			   "bnx2x_ets_E3B0_config total BW shouldn't be 0\n");
			return -EINVAL;
		}
		DP(NETIF_MSG_LINK,
		   "bnx2x_ets_E3B0_config total BW should be 100\n");
		/* We can handle a case whre the BW isn't 100 this can happen
		 * if the TC are joined.
		 */
	}
	return 0;
}