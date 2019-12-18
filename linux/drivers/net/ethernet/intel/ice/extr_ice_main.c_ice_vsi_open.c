#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ice_vsi {int /*<<< orphan*/  num_rxq; TYPE_2__* netdev; int /*<<< orphan*/  num_txq; struct ice_pf* back; } ;
struct ice_pf {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  int_name ;
struct TYPE_5__ {char* name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ICE_INT_NAME_STR_LEN ; 
 char* dev_driver_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_down (struct ice_vsi*) ; 
 int ice_up_complete (struct ice_vsi*) ; 
 int ice_vsi_cfg (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_free_irq (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_free_rx_rings (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_free_tx_rings (struct ice_vsi*) ; 
 int ice_vsi_req_irq_msix (struct ice_vsi*,char*) ; 
 int ice_vsi_setup_rx_rings (struct ice_vsi*) ; 
 int ice_vsi_setup_tx_rings (struct ice_vsi*) ; 
 int netif_set_real_num_rx_queues (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static int ice_vsi_open(struct ice_vsi *vsi)
{
	char int_name[ICE_INT_NAME_STR_LEN];
	struct ice_pf *pf = vsi->back;
	int err;

	/* allocate descriptors */
	err = ice_vsi_setup_tx_rings(vsi);
	if (err)
		goto err_setup_tx;

	err = ice_vsi_setup_rx_rings(vsi);
	if (err)
		goto err_setup_rx;

	err = ice_vsi_cfg(vsi);
	if (err)
		goto err_setup_rx;

	snprintf(int_name, sizeof(int_name) - 1, "%s-%s",
		 dev_driver_string(&pf->pdev->dev), vsi->netdev->name);
	err = ice_vsi_req_irq_msix(vsi, int_name);
	if (err)
		goto err_setup_rx;

	/* Notify the stack of the actual queue counts. */
	err = netif_set_real_num_tx_queues(vsi->netdev, vsi->num_txq);
	if (err)
		goto err_set_qs;

	err = netif_set_real_num_rx_queues(vsi->netdev, vsi->num_rxq);
	if (err)
		goto err_set_qs;

	err = ice_up_complete(vsi);
	if (err)
		goto err_up_complete;

	return 0;

err_up_complete:
	ice_down(vsi);
err_set_qs:
	ice_vsi_free_irq(vsi);
err_setup_rx:
	ice_vsi_free_rx_rings(vsi);
err_setup_tx:
	ice_vsi_free_tx_rings(vsi);

	return err;
}