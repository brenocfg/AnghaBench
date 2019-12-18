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
struct ice_vsi {int /*<<< orphan*/  tx_rings; } ;

/* Variables and functions */
 int ice_vsi_cfg_txqs (struct ice_vsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ice_vsi_cfg_lan_txqs(struct ice_vsi *vsi)
{
	return ice_vsi_cfg_txqs(vsi, vsi->tx_rings, 0);
}