#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct efx_nic {TYPE_1__* mcdi; struct efx_nic* primary; int /*<<< orphan*/  net_dev; } ;
struct efx_mcdi_iface {char* logging_buffer; int new_epoch; int /*<<< orphan*/  async_timer; int /*<<< orphan*/  async_list; int /*<<< orphan*/  async_lock; int /*<<< orphan*/  mode; int /*<<< orphan*/  state; int /*<<< orphan*/  iface_lock; int /*<<< orphan*/  proxy_rx_wq; int /*<<< orphan*/  wq; int /*<<< orphan*/  logging_enabled; struct efx_nic* efx; } ;
struct TYPE_3__ {int fn_flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MCDI_MODE_POLL ; 
 int /*<<< orphan*/  MCDI_STATE_QUIESCENT ; 
 int MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_PRIMARY ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int efx_mcdi_drv_attach (struct efx_nic*,int,int*) ; 
 int efx_mcdi_handle_assertion (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_poll_reboot (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_timeout_async ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcdi_logging_default ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int efx_mcdi_init(struct efx_nic *efx)
{
	struct efx_mcdi_iface *mcdi;
	bool already_attached;
	int rc = -ENOMEM;

	efx->mcdi = kzalloc(sizeof(*efx->mcdi), GFP_KERNEL);
	if (!efx->mcdi)
		goto fail;

	mcdi = efx_mcdi(efx);
	mcdi->efx = efx;
#ifdef CONFIG_SFC_MCDI_LOGGING
	/* consuming code assumes buffer is page-sized */
	mcdi->logging_buffer = (char *)__get_free_page(GFP_KERNEL);
	if (!mcdi->logging_buffer)
		goto fail1;
	mcdi->logging_enabled = mcdi_logging_default;
#endif
	init_waitqueue_head(&mcdi->wq);
	init_waitqueue_head(&mcdi->proxy_rx_wq);
	spin_lock_init(&mcdi->iface_lock);
	mcdi->state = MCDI_STATE_QUIESCENT;
	mcdi->mode = MCDI_MODE_POLL;
	spin_lock_init(&mcdi->async_lock);
	INIT_LIST_HEAD(&mcdi->async_list);
	timer_setup(&mcdi->async_timer, efx_mcdi_timeout_async, 0);

	(void) efx_mcdi_poll_reboot(efx);
	mcdi->new_epoch = true;

	/* Recover from a failed assertion before probing */
	rc = efx_mcdi_handle_assertion(efx);
	if (rc)
		goto fail2;

	/* Let the MC (and BMC, if this is a LOM) know that the driver
	 * is loaded. We should do this before we reset the NIC.
	 */
	rc = efx_mcdi_drv_attach(efx, true, &already_attached);
	if (rc) {
		netif_err(efx, probe, efx->net_dev,
			  "Unable to register driver with MCPU\n");
		goto fail2;
	}
	if (already_attached)
		/* Not a fatal error */
		netif_err(efx, probe, efx->net_dev,
			  "Host already registered with MCPU\n");

	if (efx->mcdi->fn_flags &
	    (1 << MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_PRIMARY))
		efx->primary = efx;

	return 0;
fail2:
#ifdef CONFIG_SFC_MCDI_LOGGING
	free_page((unsigned long)mcdi->logging_buffer);
fail1:
#endif
	kfree(efx->mcdi);
	efx->mcdi = NULL;
fail:
	return rc;
}