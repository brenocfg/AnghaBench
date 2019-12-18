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
struct ef4_nic {int /*<<< orphan*/  rx_indir_table; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_POPULATE_OWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EF4_REV_FALCON_B0 ; 
 int /*<<< orphan*/  EF4_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ EF4_WORKAROUND_5129 (struct ef4_nic*) ; 
 scalar_t__ EF4_WORKAROUND_5583 (struct ef4_nic*) ; 
 scalar_t__ EF4_WORKAROUND_7244 (struct ef4_nic*) ; 
 int /*<<< orphan*/  FRF_AA_RX_ISCSI_DIS ; 
 int /*<<< orphan*/  FRF_AA_RX_NODESC_WAIT_DIS ; 
 int /*<<< orphan*/  FRF_AA_RX_SELF_RST_EN ; 
 int /*<<< orphan*/  FRF_AB_MEM_PERR_EN_TX_DATA ; 
 int /*<<< orphan*/  FRF_AB_ONCHIP_SRAM ; 
 int /*<<< orphan*/  FRF_AZ_TX_NO_EOP_DISC_EN ; 
 int /*<<< orphan*/  FRF_BZ_FLS_EVQ_ID ; 
 int /*<<< orphan*/  FRF_BZ_TCP_FULL_SRCH_LIMIT ; 
 int /*<<< orphan*/  FRF_BZ_TCP_WILD_SRCH_LIMIT ; 
 int /*<<< orphan*/  FRF_BZ_UDP_FULL_SRCH_LIMIT ; 
 int /*<<< orphan*/  FRF_BZ_UDP_WILD_SRCH_LIMIT ; 
 int /*<<< orphan*/  FR_AA_RX_SELF_RST ; 
 int /*<<< orphan*/  FR_AB_NIC_STAT ; 
 int /*<<< orphan*/  FR_AZ_CSR_SPARE ; 
 int /*<<< orphan*/  FR_AZ_TX_CFG ; 
 int /*<<< orphan*/  FR_BZ_DP_CTRL ; 
 int /*<<< orphan*/  FR_BZ_RX_FILTER_CTL ; 
 int /*<<< orphan*/  ef4_farch_init_common (struct ef4_nic*) ; 
 scalar_t__ ef4_nic_rev (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_reado (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_writeo (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  falcon_b0_rx_push_rss_config (struct ef4_nic*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  falcon_init_rx_cfg (struct ef4_nic*) ; 
 int falcon_reset_sram (struct ef4_nic*) ; 

__attribute__((used)) static int falcon_init_nic(struct ef4_nic *efx)
{
	ef4_oword_t temp;
	int rc;

	/* Use on-chip SRAM */
	ef4_reado(efx, &temp, FR_AB_NIC_STAT);
	EF4_SET_OWORD_FIELD(temp, FRF_AB_ONCHIP_SRAM, 1);
	ef4_writeo(efx, &temp, FR_AB_NIC_STAT);

	rc = falcon_reset_sram(efx);
	if (rc)
		return rc;

	/* Clear the parity enables on the TX data fifos as
	 * they produce false parity errors because of timing issues
	 */
	if (EF4_WORKAROUND_5129(efx)) {
		ef4_reado(efx, &temp, FR_AZ_CSR_SPARE);
		EF4_SET_OWORD_FIELD(temp, FRF_AB_MEM_PERR_EN_TX_DATA, 0);
		ef4_writeo(efx, &temp, FR_AZ_CSR_SPARE);
	}

	if (EF4_WORKAROUND_7244(efx)) {
		ef4_reado(efx, &temp, FR_BZ_RX_FILTER_CTL);
		EF4_SET_OWORD_FIELD(temp, FRF_BZ_UDP_FULL_SRCH_LIMIT, 8);
		EF4_SET_OWORD_FIELD(temp, FRF_BZ_UDP_WILD_SRCH_LIMIT, 8);
		EF4_SET_OWORD_FIELD(temp, FRF_BZ_TCP_FULL_SRCH_LIMIT, 8);
		EF4_SET_OWORD_FIELD(temp, FRF_BZ_TCP_WILD_SRCH_LIMIT, 8);
		ef4_writeo(efx, &temp, FR_BZ_RX_FILTER_CTL);
	}

	/* XXX This is documented only for Falcon A0/A1 */
	/* Setup RX.  Wait for descriptor is broken and must
	 * be disabled.  RXDP recovery shouldn't be needed, but is.
	 */
	ef4_reado(efx, &temp, FR_AA_RX_SELF_RST);
	EF4_SET_OWORD_FIELD(temp, FRF_AA_RX_NODESC_WAIT_DIS, 1);
	EF4_SET_OWORD_FIELD(temp, FRF_AA_RX_SELF_RST_EN, 1);
	if (EF4_WORKAROUND_5583(efx))
		EF4_SET_OWORD_FIELD(temp, FRF_AA_RX_ISCSI_DIS, 1);
	ef4_writeo(efx, &temp, FR_AA_RX_SELF_RST);

	/* Do not enable TX_NO_EOP_DISC_EN, since it limits packets to 16
	 * descriptors (which is bad).
	 */
	ef4_reado(efx, &temp, FR_AZ_TX_CFG);
	EF4_SET_OWORD_FIELD(temp, FRF_AZ_TX_NO_EOP_DISC_EN, 0);
	ef4_writeo(efx, &temp, FR_AZ_TX_CFG);

	falcon_init_rx_cfg(efx);

	if (ef4_nic_rev(efx) >= EF4_REV_FALCON_B0) {
		falcon_b0_rx_push_rss_config(efx, false, efx->rx_indir_table);

		/* Set destination of both TX and RX Flush events */
		EF4_POPULATE_OWORD_1(temp, FRF_BZ_FLS_EVQ_ID, 0);
		ef4_writeo(efx, &temp, FR_BZ_DP_CTRL);
	}

	ef4_farch_init_common(efx);

	return 0;
}