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
struct i40e_vsi {TYPE_3__** xdp_rings; TYPE_2__** tx_rings; TYPE_1__** rx_rings; } ;
struct TYPE_6__ {int /*<<< orphan*/  stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_stats; } ;

/* Variables and functions */
 scalar_t__ i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i40e_queue_pair_reset_stats(struct i40e_vsi *vsi, int queue_pair)
{
	memset(&vsi->rx_rings[queue_pair]->rx_stats, 0,
	       sizeof(vsi->rx_rings[queue_pair]->rx_stats));
	memset(&vsi->tx_rings[queue_pair]->stats, 0,
	       sizeof(vsi->tx_rings[queue_pair]->stats));
	if (i40e_enabled_xdp_vsi(vsi)) {
		memset(&vsi->xdp_rings[queue_pair]->stats, 0,
		       sizeof(vsi->xdp_rings[queue_pair]->stats));
	}
}