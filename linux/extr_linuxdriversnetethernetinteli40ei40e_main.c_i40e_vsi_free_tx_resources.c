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
struct i40e_vsi {int num_queue_pairs; TYPE_1__** xdp_rings; TYPE_1__** tx_rings; } ;
struct TYPE_2__ {scalar_t__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_free_tx_resources (TYPE_1__*) ; 

__attribute__((used)) static void i40e_vsi_free_tx_resources(struct i40e_vsi *vsi)
{
	int i;

	if (vsi->tx_rings) {
		for (i = 0; i < vsi->num_queue_pairs; i++)
			if (vsi->tx_rings[i] && vsi->tx_rings[i]->desc)
				i40e_free_tx_resources(vsi->tx_rings[i]);
	}

	if (vsi->xdp_rings) {
		for (i = 0; i < vsi->num_queue_pairs; i++)
			if (vsi->xdp_rings[i] && vsi->xdp_rings[i]->desc)
				i40e_free_tx_resources(vsi->xdp_rings[i]);
	}
}