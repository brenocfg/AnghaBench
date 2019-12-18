#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ entries; scalar_t__ index; } ;
struct efx_rx_queue {TYPE_3__ rxd; scalar_t__ scatter_n; struct efx_nic* efx; } ;
struct efx_nic {int rx_scatter; TYPE_1__* type; int /*<<< orphan*/  net_dev; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;
struct TYPE_5__ {int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  rxd_ptr_tbl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_OWORD_10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_BUF_BASE_ID ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_EN ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_EVQ_ID ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_JUMBO ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_LABEL ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_OWNER_ID ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_SIZE ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_TYPE ; 
 int /*<<< orphan*/  FRF_AZ_RX_ISCSI_DDIG_EN ; 
 int /*<<< orphan*/  FRF_AZ_RX_ISCSI_HDIG_EN ; 
 int /*<<< orphan*/  __ffs (scalar_t__) ; 
 int /*<<< orphan*/  efx_init_special_buffer (struct efx_nic*,TYPE_3__*) ; 
 TYPE_2__* efx_rx_queue_channel (struct efx_rx_queue*) ; 
 int /*<<< orphan*/  efx_rx_queue_index (struct efx_rx_queue*) ; 
 int /*<<< orphan*/  efx_writeo_table (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void efx_farch_rx_init(struct efx_rx_queue *rx_queue)
{
	efx_oword_t rx_desc_ptr;
	struct efx_nic *efx = rx_queue->efx;
	bool jumbo_en;

	/* For kernel-mode queues in Siena, the JUMBO flag enables scatter. */
	jumbo_en = efx->rx_scatter;

	netif_dbg(efx, hw, efx->net_dev,
		  "RX queue %d ring in special buffers %d-%d\n",
		  efx_rx_queue_index(rx_queue), rx_queue->rxd.index,
		  rx_queue->rxd.index + rx_queue->rxd.entries - 1);

	rx_queue->scatter_n = 0;

	/* Pin RX descriptor ring */
	efx_init_special_buffer(efx, &rx_queue->rxd);

	/* Push RX descriptor ring to card */
	EFX_POPULATE_OWORD_10(rx_desc_ptr,
			      FRF_AZ_RX_ISCSI_DDIG_EN, true,
			      FRF_AZ_RX_ISCSI_HDIG_EN, true,
			      FRF_AZ_RX_DESCQ_BUF_BASE_ID, rx_queue->rxd.index,
			      FRF_AZ_RX_DESCQ_EVQ_ID,
			      efx_rx_queue_channel(rx_queue)->channel,
			      FRF_AZ_RX_DESCQ_OWNER_ID, 0,
			      FRF_AZ_RX_DESCQ_LABEL,
			      efx_rx_queue_index(rx_queue),
			      FRF_AZ_RX_DESCQ_SIZE,
			      __ffs(rx_queue->rxd.entries),
			      FRF_AZ_RX_DESCQ_TYPE, 0 /* kernel queue */ ,
			      FRF_AZ_RX_DESCQ_JUMBO, jumbo_en,
			      FRF_AZ_RX_DESCQ_EN, 1);
	efx_writeo_table(efx, &rx_desc_ptr, efx->type->rxd_ptr_tbl_base,
			 efx_rx_queue_index(rx_queue));
}