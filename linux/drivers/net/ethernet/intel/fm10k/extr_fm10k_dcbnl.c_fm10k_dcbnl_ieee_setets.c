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
struct net_device {int dummy; } ;
struct ieee_ets {scalar_t__* tc_tsa; int* prio_tc; scalar_t__* tc_rx_bw; scalar_t__* tc_tx_bw; } ;

/* Variables and functions */
 int EINVAL ; 
 int IEEE_8021QAZ_MAX_TCS ; 
 scalar_t__ IEEE_8021QAZ_TSA_STRICT ; 
 int fm10k_setup_tc (struct net_device*,int) ; 
 int netdev_get_num_tc (struct net_device*) ; 
 int /*<<< orphan*/  netdev_set_prio_tc_map (struct net_device*,int,int) ; 

__attribute__((used)) static int fm10k_dcbnl_ieee_setets(struct net_device *dev, struct ieee_ets *ets)
{
	u8 num_tc = 0;
	int i;

	/* verify type and determine num_tcs needed */
	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (ets->tc_tx_bw[i] || ets->tc_rx_bw[i])
			return -EINVAL;
		if (ets->tc_tsa[i] != IEEE_8021QAZ_TSA_STRICT)
			return -EINVAL;
		if (ets->prio_tc[i] > num_tc)
			num_tc = ets->prio_tc[i];
	}

	/* if requested TC is greater than 0 then num_tcs is max + 1 */
	if (num_tc)
		num_tc++;

	if (num_tc > IEEE_8021QAZ_MAX_TCS)
		return -EINVAL;

	/* update TC hardware mapping if necessary */
	if (num_tc != netdev_get_num_tc(dev)) {
		int err = fm10k_setup_tc(dev, num_tc);
		if (err)
			return err;
	}

	/* update priority mapping */
	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		netdev_set_prio_tc_map(dev, i, ets->prio_tc[i]);

	return 0;
}