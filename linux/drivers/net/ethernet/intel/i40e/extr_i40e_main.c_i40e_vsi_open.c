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
struct i40e_vsi {scalar_t__ type; int /*<<< orphan*/  num_queue_pairs; TYPE_2__* netdev; struct i40e_pf* back; } ;
struct i40e_pf {size_t lan_vsi; struct i40e_vsi** vsi; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  int_name ;
struct TYPE_5__ {char* name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int I40E_INT_NAME_STR_LEN ; 
 int /*<<< orphan*/  I40E_PF_RESET_FLAG ; 
 scalar_t__ I40E_VSI_FDIR ; 
 char* dev_driver_string (int /*<<< orphan*/ *) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_do_reset (struct i40e_pf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i40e_down (struct i40e_vsi*) ; 
 int i40e_up_complete (struct i40e_vsi*) ; 
 int i40e_vsi_configure (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_free_irq (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_free_rx_resources (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_free_tx_resources (struct i40e_vsi*) ; 
 int i40e_vsi_request_irq (struct i40e_vsi*,char*) ; 
 int i40e_vsi_setup_rx_resources (struct i40e_vsi*) ; 
 int i40e_vsi_setup_tx_resources (struct i40e_vsi*) ; 
 int netif_set_real_num_rx_queues (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

int i40e_vsi_open(struct i40e_vsi *vsi)
{
	struct i40e_pf *pf = vsi->back;
	char int_name[I40E_INT_NAME_STR_LEN];
	int err;

	/* allocate descriptors */
	err = i40e_vsi_setup_tx_resources(vsi);
	if (err)
		goto err_setup_tx;
	err = i40e_vsi_setup_rx_resources(vsi);
	if (err)
		goto err_setup_rx;

	err = i40e_vsi_configure(vsi);
	if (err)
		goto err_setup_rx;

	if (vsi->netdev) {
		snprintf(int_name, sizeof(int_name) - 1, "%s-%s",
			 dev_driver_string(&pf->pdev->dev), vsi->netdev->name);
		err = i40e_vsi_request_irq(vsi, int_name);
		if (err)
			goto err_setup_rx;

		/* Notify the stack of the actual queue counts. */
		err = netif_set_real_num_tx_queues(vsi->netdev,
						   vsi->num_queue_pairs);
		if (err)
			goto err_set_queues;

		err = netif_set_real_num_rx_queues(vsi->netdev,
						   vsi->num_queue_pairs);
		if (err)
			goto err_set_queues;

	} else if (vsi->type == I40E_VSI_FDIR) {
		snprintf(int_name, sizeof(int_name) - 1, "%s-%s:fdir",
			 dev_driver_string(&pf->pdev->dev),
			 dev_name(&pf->pdev->dev));
		err = i40e_vsi_request_irq(vsi, int_name);

	} else {
		err = -EINVAL;
		goto err_setup_rx;
	}

	err = i40e_up_complete(vsi);
	if (err)
		goto err_up_complete;

	return 0;

err_up_complete:
	i40e_down(vsi);
err_set_queues:
	i40e_vsi_free_irq(vsi);
err_setup_rx:
	i40e_vsi_free_rx_resources(vsi);
err_setup_tx:
	i40e_vsi_free_tx_resources(vsi);
	if (vsi == pf->vsi[pf->lan_vsi])
		i40e_do_reset(pf, I40E_PF_RESET_FLAG, true);

	return err;
}