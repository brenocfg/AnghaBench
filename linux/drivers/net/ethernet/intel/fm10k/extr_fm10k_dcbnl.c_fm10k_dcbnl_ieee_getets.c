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
struct ieee_ets {int ets_cap; int /*<<< orphan*/ * prio_tc; int /*<<< orphan*/  tc_tsa; int /*<<< orphan*/  tc_rx_bw; int /*<<< orphan*/  tc_tx_bw; scalar_t__ cbs; } ;

/* Variables and functions */
 int IEEE_8021QAZ_MAX_TCS ; 
 int /*<<< orphan*/  IEEE_8021QAZ_TSA_STRICT ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_get_prio_tc_map (struct net_device*,int) ; 

__attribute__((used)) static int fm10k_dcbnl_ieee_getets(struct net_device *dev, struct ieee_ets *ets)
{
	int i;

	/* we support 8 TCs in all modes */
	ets->ets_cap = IEEE_8021QAZ_MAX_TCS;
	ets->cbs = 0;

	/* we only support strict priority and cannot do traffic shaping */
	memset(ets->tc_tx_bw, 0, sizeof(ets->tc_tx_bw));
	memset(ets->tc_rx_bw, 0, sizeof(ets->tc_rx_bw));
	memset(ets->tc_tsa, IEEE_8021QAZ_TSA_STRICT, sizeof(ets->tc_tsa));

	/* populate the prio map based on the netdev */
	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		ets->prio_tc[i] = netdev_get_prio_tc_map(dev, i);

	return 0;
}