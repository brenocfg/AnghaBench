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
typedef  int /*<<< orphan*/  u8 ;
struct hfi1_vnic_vport_info {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_vnic_sdma_write_avail (struct hfi1_vnic_vport_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfi1_vnic_maybe_stop_tx(struct hfi1_vnic_vport_info *vinfo,
				    u8 q_idx)
{
	netif_stop_subqueue(vinfo->netdev, q_idx);
	if (!hfi1_vnic_sdma_write_avail(vinfo, q_idx))
		return;

	netif_start_subqueue(vinfo->netdev, q_idx);
}