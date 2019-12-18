#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct msix_entry {unsigned int entry; int /*<<< orphan*/  vector; } ;
struct ef4_nic {scalar_t__ interrupt_mode; unsigned int n_channels; unsigned int n_tx_channels; unsigned int n_rx_channels; int rss_spread; TYPE_1__** extra_channel_type; TYPE_2__* pci_dev; int /*<<< orphan*/  legacy_irq; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  max_tx_channels; int /*<<< orphan*/  max_channels; } ;
struct TYPE_7__ {TYPE_1__* type; int /*<<< orphan*/  irq; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* handle_no_channel ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 scalar_t__ EF4_INT_MODE_LEGACY ; 
 scalar_t__ EF4_INT_MODE_MSI ; 
 scalar_t__ EF4_INT_MODE_MSIX ; 
 int EF4_MAX_CHANNELS ; 
 unsigned int EF4_MAX_EXTRA_CHANNELS ; 
 int /*<<< orphan*/  drv ; 
 TYPE_4__* ef4_get_channel (struct ef4_nic*,unsigned int) ; 
 scalar_t__ ef4_separate_tx_channels ; 
 unsigned int ef4_wanted_parallelism (struct ef4_nic*) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 void* min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int pci_enable_msi (TYPE_2__*) ; 
 int pci_enable_msix_range (TYPE_2__*,struct msix_entry*,int,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*) ; 

__attribute__((used)) static int ef4_probe_interrupts(struct ef4_nic *efx)
{
	unsigned int extra_channels = 0;
	unsigned int i, j;
	int rc;

	for (i = 0; i < EF4_MAX_EXTRA_CHANNELS; i++)
		if (efx->extra_channel_type[i])
			++extra_channels;

	if (efx->interrupt_mode == EF4_INT_MODE_MSIX) {
		struct msix_entry xentries[EF4_MAX_CHANNELS];
		unsigned int n_channels;

		n_channels = ef4_wanted_parallelism(efx);
		if (ef4_separate_tx_channels)
			n_channels *= 2;
		n_channels += extra_channels;
		n_channels = min(n_channels, efx->max_channels);

		for (i = 0; i < n_channels; i++)
			xentries[i].entry = i;
		rc = pci_enable_msix_range(efx->pci_dev,
					   xentries, 1, n_channels);
		if (rc < 0) {
			/* Fall back to single channel MSI */
			efx->interrupt_mode = EF4_INT_MODE_MSI;
			netif_err(efx, drv, efx->net_dev,
				  "could not enable MSI-X\n");
		} else if (rc < n_channels) {
			netif_err(efx, drv, efx->net_dev,
				  "WARNING: Insufficient MSI-X vectors"
				  " available (%d < %u).\n", rc, n_channels);
			netif_err(efx, drv, efx->net_dev,
				  "WARNING: Performance may be reduced.\n");
			n_channels = rc;
		}

		if (rc > 0) {
			efx->n_channels = n_channels;
			if (n_channels > extra_channels)
				n_channels -= extra_channels;
			if (ef4_separate_tx_channels) {
				efx->n_tx_channels = min(max(n_channels / 2,
							     1U),
							 efx->max_tx_channels);
				efx->n_rx_channels = max(n_channels -
							 efx->n_tx_channels,
							 1U);
			} else {
				efx->n_tx_channels = min(n_channels,
							 efx->max_tx_channels);
				efx->n_rx_channels = n_channels;
			}
			for (i = 0; i < efx->n_channels; i++)
				ef4_get_channel(efx, i)->irq =
					xentries[i].vector;
		}
	}

	/* Try single interrupt MSI */
	if (efx->interrupt_mode == EF4_INT_MODE_MSI) {
		efx->n_channels = 1;
		efx->n_rx_channels = 1;
		efx->n_tx_channels = 1;
		rc = pci_enable_msi(efx->pci_dev);
		if (rc == 0) {
			ef4_get_channel(efx, 0)->irq = efx->pci_dev->irq;
		} else {
			netif_err(efx, drv, efx->net_dev,
				  "could not enable MSI\n");
			efx->interrupt_mode = EF4_INT_MODE_LEGACY;
		}
	}

	/* Assume legacy interrupts */
	if (efx->interrupt_mode == EF4_INT_MODE_LEGACY) {
		efx->n_channels = 1 + (ef4_separate_tx_channels ? 1 : 0);
		efx->n_rx_channels = 1;
		efx->n_tx_channels = 1;
		efx->legacy_irq = efx->pci_dev->irq;
	}

	/* Assign extra channels if possible */
	j = efx->n_channels;
	for (i = 0; i < EF4_MAX_EXTRA_CHANNELS; i++) {
		if (!efx->extra_channel_type[i])
			continue;
		if (efx->interrupt_mode != EF4_INT_MODE_MSIX ||
		    efx->n_channels <= extra_channels) {
			efx->extra_channel_type[i]->handle_no_channel(efx);
		} else {
			--j;
			ef4_get_channel(efx, j)->type =
				efx->extra_channel_type[i];
		}
	}

	efx->rss_spread = efx->n_rx_channels;

	return 0;
}