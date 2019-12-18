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
struct TYPE_6__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  index; } ;
struct efx_tx_queue {int queue; TYPE_3__ txd; TYPE_1__* channel; struct efx_nic* efx; } ;
struct efx_nic {TYPE_2__* type; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;
struct TYPE_5__ {int /*<<< orphan*/  txd_ptr_tbl_base; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_OWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EFX_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int EFX_TXQ_TYPE_HIGHPRI ; 
 int EFX_TXQ_TYPE_OFFLOAD ; 
 int /*<<< orphan*/  FFE_BZ_TX_PACE_OFF ; 
 int /*<<< orphan*/  FFE_BZ_TX_PACE_RESERVED ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_BUF_BASE_ID ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_EN ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_EVQ_ID ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_LABEL ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_OWNER_ID ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_SIZE ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_TYPE ; 
 int /*<<< orphan*/  FRF_AZ_TX_ISCSI_DDIG_EN ; 
 int /*<<< orphan*/  FRF_AZ_TX_ISCSI_HDIG_EN ; 
 int /*<<< orphan*/  FRF_BZ_TX_IP_CHKSM_DIS ; 
 int /*<<< orphan*/  FRF_BZ_TX_NON_IP_DROP_DIS ; 
 int /*<<< orphan*/  FRF_BZ_TX_PACE ; 
 int /*<<< orphan*/  FRF_BZ_TX_TCP_CHKSM_DIS ; 
 int /*<<< orphan*/  FR_BZ_TX_PACE_TBL ; 
 int /*<<< orphan*/  __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_init_special_buffer (struct efx_nic*,TYPE_3__*) ; 
 int /*<<< orphan*/  efx_writeo_table (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void efx_farch_tx_init(struct efx_tx_queue *tx_queue)
{
	int csum = tx_queue->queue & EFX_TXQ_TYPE_OFFLOAD;
	struct efx_nic *efx = tx_queue->efx;
	efx_oword_t reg;

	/* Pin TX descriptor ring */
	efx_init_special_buffer(efx, &tx_queue->txd);

	/* Push TX descriptor ring to card */
	EFX_POPULATE_OWORD_10(reg,
			      FRF_AZ_TX_DESCQ_EN, 1,
			      FRF_AZ_TX_ISCSI_DDIG_EN, 0,
			      FRF_AZ_TX_ISCSI_HDIG_EN, 0,
			      FRF_AZ_TX_DESCQ_BUF_BASE_ID, tx_queue->txd.index,
			      FRF_AZ_TX_DESCQ_EVQ_ID,
			      tx_queue->channel->channel,
			      FRF_AZ_TX_DESCQ_OWNER_ID, 0,
			      FRF_AZ_TX_DESCQ_LABEL, tx_queue->queue,
			      FRF_AZ_TX_DESCQ_SIZE,
			      __ffs(tx_queue->txd.entries),
			      FRF_AZ_TX_DESCQ_TYPE, 0,
			      FRF_BZ_TX_NON_IP_DROP_DIS, 1);

	EFX_SET_OWORD_FIELD(reg, FRF_BZ_TX_IP_CHKSM_DIS, !csum);
	EFX_SET_OWORD_FIELD(reg, FRF_BZ_TX_TCP_CHKSM_DIS, !csum);

	efx_writeo_table(efx, &reg, efx->type->txd_ptr_tbl_base,
			 tx_queue->queue);

	EFX_POPULATE_OWORD_1(reg,
			     FRF_BZ_TX_PACE,
			     (tx_queue->queue & EFX_TXQ_TYPE_HIGHPRI) ?
			     FFE_BZ_TX_PACE_OFF :
			     FFE_BZ_TX_PACE_RESERVED);
	efx_writeo_table(efx, &reg, FR_BZ_TX_PACE_TBL, tx_queue->queue);
}