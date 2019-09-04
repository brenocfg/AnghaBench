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
struct net_device {int dummy; } ;
struct ieee_ets {scalar_t__* prio_tc; scalar_t__* tc_tsa; scalar_t__* tc_tx_bw; } ;

/* Variables and functions */
 int EINVAL ; 
 int IEEE_8021QAZ_MAX_TCS ; 
 scalar_t__ IEEE_8021QAZ_TSA_ETS ; 
 scalar_t__ MLX5E_MAX_PRIORITY ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 

__attribute__((used)) static int mlx5e_dbcnl_validate_ets(struct net_device *netdev,
				    struct ieee_ets *ets,
				    bool zero_sum_allowed)
{
	bool have_ets_tc = false;
	int bw_sum = 0;
	int i;

	/* Validate Priority */
	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (ets->prio_tc[i] >= MLX5E_MAX_PRIORITY) {
			netdev_err(netdev,
				   "Failed to validate ETS: priority value greater than max(%d)\n",
				    MLX5E_MAX_PRIORITY);
			return -EINVAL;
		}
	}

	/* Validate Bandwidth Sum */
	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (ets->tc_tsa[i] == IEEE_8021QAZ_TSA_ETS) {
			have_ets_tc = true;
			bw_sum += ets->tc_tx_bw[i];
		}
	}

	if (have_ets_tc && bw_sum != 100) {
		if (bw_sum || (!bw_sum && !zero_sum_allowed))
			netdev_err(netdev,
				   "Failed to validate ETS: BW sum is illegal\n");
		return -EINVAL;
	}
	return 0;
}