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
struct TYPE_2__ {int /*<<< orphan*/  tx_flow_on; int /*<<< orphan*/  tx_kicks; int /*<<< orphan*/  tx_no_mem; int /*<<< orphan*/  tx_full_ring; int /*<<< orphan*/  rx_kicks; int /*<<< orphan*/  rx_nomem; int /*<<< orphan*/  rx_napi_resched; int /*<<< orphan*/  rx_napi_complete; } ;
struct cfv_info {TYPE_1__ stats; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void debugfs_init(struct cfv_info *cfv)
{
	cfv->debugfs = debugfs_create_dir(netdev_name(cfv->ndev), NULL);

	debugfs_create_u32("rx-napi-complete", 0400, cfv->debugfs,
			   &cfv->stats.rx_napi_complete);
	debugfs_create_u32("rx-napi-resched", 0400, cfv->debugfs,
			   &cfv->stats.rx_napi_resched);
	debugfs_create_u32("rx-nomem", 0400, cfv->debugfs,
			   &cfv->stats.rx_nomem);
	debugfs_create_u32("rx-kicks", 0400, cfv->debugfs,
			   &cfv->stats.rx_kicks);
	debugfs_create_u32("tx-full-ring", 0400, cfv->debugfs,
			   &cfv->stats.tx_full_ring);
	debugfs_create_u32("tx-no-mem", 0400, cfv->debugfs,
			   &cfv->stats.tx_no_mem);
	debugfs_create_u32("tx-kicks", 0400, cfv->debugfs,
			   &cfv->stats.tx_kicks);
	debugfs_create_u32("tx-flow-on", 0400, cfv->debugfs,
			   &cfv->stats.tx_flow_on);
}