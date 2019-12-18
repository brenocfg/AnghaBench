#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int len; scalar_t__ dma_addr; } ;
struct TYPE_7__ {TYPE_2__ buf; } ;
struct efx_tx_queue {int queue; int timestamping; int ptr_mask; int insert_count; int write_count; int tso_version; int /*<<< orphan*/  handle_tso; TYPE_4__* buffer; TYPE_3__ txd; struct efx_nic* efx; struct efx_channel* channel; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; TYPE_1__* type; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int licensed_features; int datapath_caps2; int vport_id; int datapath_caps; } ;
struct efx_channel {int channel; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ptp_set_ts_sync_events ) (struct efx_nic*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EFX_BUF_SIZE ; 
 int EFX_MAX_DMAQ_SIZE ; 
 int /*<<< orphan*/  EFX_POPULATE_QWORD_5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int EFX_TXQ_TYPE_OFFLOAD ; 
 int /*<<< orphan*/  EFX_TX_BUF_OPTION ; 
 int ENOSPC ; 
 int /*<<< orphan*/  ESE_DZ_TX_OPTION_DESC_CRC_CSUM ; 
 int /*<<< orphan*/  ESF_DZ_TX_DESC_IS_OPT ; 
 int /*<<< orphan*/  ESF_DZ_TX_OPTION_IP_CSUM ; 
 int /*<<< orphan*/  ESF_DZ_TX_OPTION_TYPE ; 
 int /*<<< orphan*/  ESF_DZ_TX_OPTION_UDP_TCP_CSUM ; 
 int /*<<< orphan*/  ESF_DZ_TX_TIMESTAMP ; 
 int /*<<< orphan*/  INIT_TXQ_EXT_IN_FLAG_TIMESTAMP ; 
 int /*<<< orphan*/  INIT_TXQ_EXT_IN_FLAG_TSOV2_EN ; 
 int /*<<< orphan*/  INIT_TXQ_IN_DMA_ADDR ; 
 int /*<<< orphan*/  INIT_TXQ_IN_FLAGS ; 
 int /*<<< orphan*/  INIT_TXQ_IN_FLAG_IP_CSUM_DIS ; 
 int /*<<< orphan*/  INIT_TXQ_IN_FLAG_TCP_CSUM_DIS ; 
 int /*<<< orphan*/  INIT_TXQ_IN_INSTANCE ; 
 int /*<<< orphan*/  INIT_TXQ_IN_LABEL ; 
 int /*<<< orphan*/  INIT_TXQ_IN_OWNER_ID ; 
 int /*<<< orphan*/  INIT_TXQ_IN_PORT_ID ; 
 int /*<<< orphan*/  INIT_TXQ_IN_SIZE ; 
 int /*<<< orphan*/  INIT_TXQ_IN_TARGET_EVQ ; 
 int LICENSED_V3_FEATURES_TX_TIMESTAMPS_LBN ; 
 int /*<<< orphan*/  MCDI_DECLARE_BUF (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  MCDI_POPULATE_DWORD_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MCDI_SET_ARRAY_QWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  MCDI_SET_DWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MC_CMD_GET_CAPABILITIES_OUT_TX_TSO_LBN ; 
 int MC_CMD_GET_CAPABILITIES_V2_OUT_TX_TSO_V2_LBN ; 
 int /*<<< orphan*/  MC_CMD_INIT_TXQ ; 
 int /*<<< orphan*/  MC_CMD_INIT_TXQ_EXT_IN_LEN ; 
 size_t MC_CMD_INIT_TXQ_IN_LEN (size_t) ; 
 scalar_t__ MC_CMD_INIT_TXQ_OUT_LEN ; 
 int /*<<< orphan*/  efx_ef10_push_tx_desc (struct efx_tx_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_ef10_tx_tso_desc ; 
 int /*<<< orphan*/  efx_mcdi_display_error (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int efx_mcdi_rpc_quiet (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * efx_tx_desc (struct efx_tx_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  inbuf ; 
 int /*<<< orphan*/  netdev_WARN (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  netif_warn (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*,int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void efx_ef10_tx_init(struct efx_tx_queue *tx_queue)
{
	MCDI_DECLARE_BUF(inbuf, MC_CMD_INIT_TXQ_IN_LEN(EFX_MAX_DMAQ_SIZE * 8 /
						       EFX_BUF_SIZE));
	bool csum_offload = tx_queue->queue & EFX_TXQ_TYPE_OFFLOAD;
	size_t entries = tx_queue->txd.buf.len / EFX_BUF_SIZE;
	struct efx_channel *channel = tx_queue->channel;
	struct efx_nic *efx = tx_queue->efx;
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	bool tso_v2 = false;
	size_t inlen;
	dma_addr_t dma_addr;
	efx_qword_t *txd;
	int rc;
	int i;
	BUILD_BUG_ON(MC_CMD_INIT_TXQ_OUT_LEN != 0);

	/* Only attempt to enable TX timestamping if we have the license for it,
	 * otherwise TXQ init will fail
	 */
	if (!(nic_data->licensed_features &
	      (1 << LICENSED_V3_FEATURES_TX_TIMESTAMPS_LBN))) {
		tx_queue->timestamping = false;
		/* Disable sync events on this channel. */
		if (efx->type->ptp_set_ts_sync_events)
			efx->type->ptp_set_ts_sync_events(efx, false, false);
	}

	/* TSOv2 is a limited resource that can only be configured on a limited
	 * number of queues. TSO without checksum offload is not really a thing,
	 * so we only enable it for those queues.
	 * TSOv2 cannot be used with Hardware timestamping.
	 */
	if (csum_offload && (nic_data->datapath_caps2 &
			(1 << MC_CMD_GET_CAPABILITIES_V2_OUT_TX_TSO_V2_LBN)) &&
	    !tx_queue->timestamping) {
		tso_v2 = true;
		netif_dbg(efx, hw, efx->net_dev, "Using TSOv2 for channel %u\n",
				channel->channel);
	}

	MCDI_SET_DWORD(inbuf, INIT_TXQ_IN_SIZE, tx_queue->ptr_mask + 1);
	MCDI_SET_DWORD(inbuf, INIT_TXQ_IN_TARGET_EVQ, channel->channel);
	MCDI_SET_DWORD(inbuf, INIT_TXQ_IN_LABEL, tx_queue->queue);
	MCDI_SET_DWORD(inbuf, INIT_TXQ_IN_INSTANCE, tx_queue->queue);
	MCDI_SET_DWORD(inbuf, INIT_TXQ_IN_OWNER_ID, 0);
	MCDI_SET_DWORD(inbuf, INIT_TXQ_IN_PORT_ID, nic_data->vport_id);

	dma_addr = tx_queue->txd.buf.dma_addr;

	netif_dbg(efx, hw, efx->net_dev, "pushing TXQ %d. %zu entries (%llx)\n",
		  tx_queue->queue, entries, (u64)dma_addr);

	for (i = 0; i < entries; ++i) {
		MCDI_SET_ARRAY_QWORD(inbuf, INIT_TXQ_IN_DMA_ADDR, i, dma_addr);
		dma_addr += EFX_BUF_SIZE;
	}

	inlen = MC_CMD_INIT_TXQ_IN_LEN(entries);

	do {
		MCDI_POPULATE_DWORD_4(inbuf, INIT_TXQ_IN_FLAGS,
				/* This flag was removed from mcdi_pcol.h for
				 * the non-_EXT version of INIT_TXQ.  However,
				 * firmware still honours it.
				 */
				INIT_TXQ_EXT_IN_FLAG_TSOV2_EN, tso_v2,
				INIT_TXQ_IN_FLAG_IP_CSUM_DIS, !csum_offload,
				INIT_TXQ_IN_FLAG_TCP_CSUM_DIS, !csum_offload,
				INIT_TXQ_EXT_IN_FLAG_TIMESTAMP,
						tx_queue->timestamping);

		rc = efx_mcdi_rpc_quiet(efx, MC_CMD_INIT_TXQ, inbuf, inlen,
					NULL, 0, NULL);
		if (rc == -ENOSPC && tso_v2) {
			/* Retry without TSOv2 if we're short on contexts. */
			tso_v2 = false;
			netif_warn(efx, probe, efx->net_dev,
				   "TSOv2 context not available to segment in hardware. TCP performance may be reduced.\n");
		} else if (rc) {
			efx_mcdi_display_error(efx, MC_CMD_INIT_TXQ,
					       MC_CMD_INIT_TXQ_EXT_IN_LEN,
					       NULL, 0, rc);
			goto fail;
		}
	} while (rc);

	/* A previous user of this TX queue might have set us up the
	 * bomb by writing a descriptor to the TX push collector but
	 * not the doorbell.  (Each collector belongs to a port, not a
	 * queue or function, so cannot easily be reset.)  We must
	 * attempt to push a no-op descriptor in its place.
	 */
	tx_queue->buffer[0].flags = EFX_TX_BUF_OPTION;
	tx_queue->insert_count = 1;
	txd = efx_tx_desc(tx_queue, 0);
	EFX_POPULATE_QWORD_5(*txd,
			     ESF_DZ_TX_DESC_IS_OPT, true,
			     ESF_DZ_TX_OPTION_TYPE,
			     ESE_DZ_TX_OPTION_DESC_CRC_CSUM,
			     ESF_DZ_TX_OPTION_UDP_TCP_CSUM, csum_offload,
			     ESF_DZ_TX_OPTION_IP_CSUM, csum_offload,
			     ESF_DZ_TX_TIMESTAMP, tx_queue->timestamping);
	tx_queue->write_count = 1;

	if (tso_v2) {
		tx_queue->handle_tso = efx_ef10_tx_tso_desc;
		tx_queue->tso_version = 2;
	} else if (nic_data->datapath_caps &
			(1 << MC_CMD_GET_CAPABILITIES_OUT_TX_TSO_LBN)) {
		tx_queue->tso_version = 1;
	}

	wmb();
	efx_ef10_push_tx_desc(tx_queue, txd);

	return;

fail:
	netdev_WARN(efx->net_dev, "failed to initialise TXQ %d\n",
		    tx_queue->queue);
}