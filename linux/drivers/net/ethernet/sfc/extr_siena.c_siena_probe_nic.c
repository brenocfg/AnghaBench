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
struct siena_nic_data {struct efx_nic* efx; } ;
struct TYPE_5__ {int dma_addr; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  prtad; } ;
struct efx_nic {struct siena_nic_data* nic_data; TYPE_2__ irq_status; TYPE_1__ mdio; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  net_dev; scalar_t__ port_num; void* max_tx_channels; void* max_channels; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 void* EFX_MAX_CHANNELS ; 
 scalar_t__ EFX_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FRF_CZ_CS_PORT_NUM ; 
 int /*<<< orphan*/  FR_AZ_CS_DEBUG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MDIO_PRTAD_NONE ; 
 int /*<<< orphan*/  PHY_TYPE_NONE ; 
 int /*<<< orphan*/  RESET_TYPE_ALL ; 
 scalar_t__ efx_farch_fpga_ver (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_detach (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_fini (struct efx_nic*) ; 
 int efx_mcdi_init (struct efx_nic*) ; 
 int efx_mcdi_mon_probe (struct efx_nic*) ; 
 int efx_mcdi_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int efx_nic_alloc_buffer (struct efx_nic*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_nic_free_buffer (struct efx_nic*,TYPE_2__*) ; 
 int /*<<< orphan*/  efx_ptp_defer_probe_with_channel (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_siena_sriov_probe (struct efx_nic*) ; 
 int /*<<< orphan*/  kfree (struct siena_nic_data*) ; 
 struct siena_nic_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  siena_init_wol (struct efx_nic*) ; 
 int siena_probe_nvconfig (struct efx_nic*) ; 
 scalar_t__ virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int siena_probe_nic(struct efx_nic *efx)
{
	struct siena_nic_data *nic_data;
	efx_oword_t reg;
	int rc;

	/* Allocate storage for hardware specific data */
	nic_data = kzalloc(sizeof(struct siena_nic_data), GFP_KERNEL);
	if (!nic_data)
		return -ENOMEM;
	nic_data->efx = efx;
	efx->nic_data = nic_data;

	if (efx_farch_fpga_ver(efx) != 0) {
		netif_err(efx, probe, efx->net_dev,
			  "Siena FPGA not supported\n");
		rc = -ENODEV;
		goto fail1;
	}

	efx->max_channels = EFX_MAX_CHANNELS;
	efx->max_tx_channels = EFX_MAX_CHANNELS;

	efx_reado(efx, &reg, FR_AZ_CS_DEBUG);
	efx->port_num = EFX_OWORD_FIELD(reg, FRF_CZ_CS_PORT_NUM) - 1;

	rc = efx_mcdi_init(efx);
	if (rc)
		goto fail1;

	/* Now we can reset the NIC */
	rc = efx_mcdi_reset(efx, RESET_TYPE_ALL);
	if (rc) {
		netif_err(efx, probe, efx->net_dev, "failed to reset NIC\n");
		goto fail3;
	}

	siena_init_wol(efx);

	/* Allocate memory for INT_KER */
	rc = efx_nic_alloc_buffer(efx, &efx->irq_status, sizeof(efx_oword_t),
				  GFP_KERNEL);
	if (rc)
		goto fail4;
	BUG_ON(efx->irq_status.dma_addr & 0x0f);

	netif_dbg(efx, probe, efx->net_dev,
		  "INT_KER at %llx (virt %p phys %llx)\n",
		  (unsigned long long)efx->irq_status.dma_addr,
		  efx->irq_status.addr,
		  (unsigned long long)virt_to_phys(efx->irq_status.addr));

	/* Read in the non-volatile configuration */
	rc = siena_probe_nvconfig(efx);
	if (rc == -EINVAL) {
		netif_err(efx, probe, efx->net_dev,
			  "NVRAM is invalid therefore using defaults\n");
		efx->phy_type = PHY_TYPE_NONE;
		efx->mdio.prtad = MDIO_PRTAD_NONE;
	} else if (rc) {
		goto fail5;
	}

	rc = efx_mcdi_mon_probe(efx);
	if (rc)
		goto fail5;

#ifdef CONFIG_SFC_SRIOV
	efx_siena_sriov_probe(efx);
#endif
	efx_ptp_defer_probe_with_channel(efx);

	return 0;

fail5:
	efx_nic_free_buffer(efx, &efx->irq_status);
fail4:
fail3:
	efx_mcdi_detach(efx);
	efx_mcdi_fini(efx);
fail1:
	kfree(efx->nic_data);
	return rc;
}