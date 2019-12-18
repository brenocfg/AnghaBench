#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct efx_tx_queue {int /*<<< orphan*/  txd; int /*<<< orphan*/  queue; struct efx_nic* efx; } ;
struct efx_nic {TYPE_1__* type; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;
struct TYPE_2__ {int /*<<< orphan*/  txd_ptr_tbl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_ZERO_OWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_fini_special_buffer (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_writeo_table (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void efx_farch_tx_fini(struct efx_tx_queue *tx_queue)
{
	struct efx_nic *efx = tx_queue->efx;
	efx_oword_t tx_desc_ptr;

	/* Remove TX descriptor ring from card */
	EFX_ZERO_OWORD(tx_desc_ptr);
	efx_writeo_table(efx, &tx_desc_ptr, efx->type->txd_ptr_tbl_base,
			 tx_queue->queue);

	/* Unpin TX descriptor ring */
	efx_fini_special_buffer(efx, &tx_queue->txd);
}