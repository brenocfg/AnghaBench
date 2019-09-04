#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ice_vsi {TYPE_2__* back; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int ice_vsi_stop_rx_rings (struct ice_vsi*) ; 
 int ice_vsi_stop_tx_rings (struct ice_vsi*) ; 

__attribute__((used)) static int ice_vsi_stop_tx_rx_rings(struct ice_vsi *vsi)
{
	int err_tx, err_rx;

	err_tx = ice_vsi_stop_tx_rings(vsi);
	if (err_tx)
		dev_dbg(&vsi->back->pdev->dev, "Failed to disable Tx rings\n");

	err_rx = ice_vsi_stop_rx_rings(vsi);
	if (err_rx)
		dev_dbg(&vsi->back->pdev->dev, "Failed to disable Rx rings\n");

	if (err_tx || err_rx)
		return -EIO;

	return 0;
}