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
struct bnx2x_rss_config_obj {int /*<<< orphan*/  ind_table; scalar_t__ udp_rss_v6; scalar_t__ udp_rss_v4; } ;
struct bnx2x_config_rss_params {int /*<<< orphan*/  rss_flags; int /*<<< orphan*/  rss_key; int /*<<< orphan*/  ind_table; int /*<<< orphan*/  rss_result_mask; int /*<<< orphan*/  ramrod_flags; struct bnx2x_rss_config_obj* rss_obj; int /*<<< orphan*/ * member_0; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_RSS_IPV4 ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV4_TCP ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV4_UDP ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV4_VXLAN ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV6 ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV6_TCP ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV6_UDP ; 
 int /*<<< orphan*/  BNX2X_RSS_IPV6_VXLAN ; 
 int /*<<< orphan*/  BNX2X_RSS_MODE_DISABLED ; 
 int /*<<< orphan*/  BNX2X_RSS_MODE_REGULAR ; 
 int /*<<< orphan*/  BNX2X_RSS_SET_SRCH ; 
 int /*<<< orphan*/  BNX2X_RSS_TUNN_INNER_HDRS ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ IS_PF (struct bnx2x*) ; 
 int /*<<< orphan*/  MULTI_MASK ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int T_ETH_RSS_KEY ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bnx2x_config_rss (struct bnx2x*,struct bnx2x_config_rss_params*) ; 
 int bnx2x_vfpf_config_rss (struct bnx2x*,struct bnx2x_config_rss_params*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (int /*<<< orphan*/ ,int) ; 

int bnx2x_rss(struct bnx2x *bp, struct bnx2x_rss_config_obj *rss_obj,
	      bool config_hash, bool enable)
{
	struct bnx2x_config_rss_params params = {NULL};

	/* Although RSS is meaningless when there is a single HW queue we
	 * still need it enabled in order to have HW Rx hash generated.
	 *
	 * if (!is_eth_multi(bp))
	 *      bp->multi_mode = ETH_RSS_MODE_DISABLED;
	 */

	params.rss_obj = rss_obj;

	__set_bit(RAMROD_COMP_WAIT, &params.ramrod_flags);

	if (enable) {
		__set_bit(BNX2X_RSS_MODE_REGULAR, &params.rss_flags);

		/* RSS configuration */
		__set_bit(BNX2X_RSS_IPV4, &params.rss_flags);
		__set_bit(BNX2X_RSS_IPV4_TCP, &params.rss_flags);
		__set_bit(BNX2X_RSS_IPV6, &params.rss_flags);
		__set_bit(BNX2X_RSS_IPV6_TCP, &params.rss_flags);
		if (rss_obj->udp_rss_v4)
			__set_bit(BNX2X_RSS_IPV4_UDP, &params.rss_flags);
		if (rss_obj->udp_rss_v6)
			__set_bit(BNX2X_RSS_IPV6_UDP, &params.rss_flags);

		if (!CHIP_IS_E1x(bp)) {
			/* valid only for TUNN_MODE_VXLAN tunnel mode */
			__set_bit(BNX2X_RSS_IPV4_VXLAN, &params.rss_flags);
			__set_bit(BNX2X_RSS_IPV6_VXLAN, &params.rss_flags);

			/* valid only for TUNN_MODE_GRE tunnel mode */
			__set_bit(BNX2X_RSS_TUNN_INNER_HDRS, &params.rss_flags);
		}
	} else {
		__set_bit(BNX2X_RSS_MODE_DISABLED, &params.rss_flags);
	}

	/* Hash bits */
	params.rss_result_mask = MULTI_MASK;

	memcpy(params.ind_table, rss_obj->ind_table, sizeof(params.ind_table));

	if (config_hash) {
		/* RSS keys */
		netdev_rss_key_fill(params.rss_key, T_ETH_RSS_KEY * 4);
		__set_bit(BNX2X_RSS_SET_SRCH, &params.rss_flags);
	}

	if (IS_PF(bp))
		return bnx2x_config_rss(bp, &params);
	else
		return bnx2x_vfpf_config_rss(bp, &params);
}