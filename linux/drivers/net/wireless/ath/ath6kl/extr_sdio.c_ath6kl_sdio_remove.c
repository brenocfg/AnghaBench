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
struct sdio_func {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; int /*<<< orphan*/  num; } ;
struct ath6kl_sdio {struct ath6kl_sdio* dma_buffer; int /*<<< orphan*/  ar; int /*<<< orphan*/  wr_async_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BOOT ; 
 int /*<<< orphan*/  ath6kl_core_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_core_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_stop_txrx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ath6kl_sdio*) ; 
 struct ath6kl_sdio* sdio_get_drvdata (struct sdio_func*) ; 

__attribute__((used)) static void ath6kl_sdio_remove(struct sdio_func *func)
{
	struct ath6kl_sdio *ar_sdio;

	ath6kl_dbg(ATH6KL_DBG_BOOT,
		   "sdio removed func %d vendor 0x%x device 0x%x\n",
		   func->num, func->vendor, func->device);

	ar_sdio = sdio_get_drvdata(func);

	ath6kl_stop_txrx(ar_sdio->ar);
	cancel_work_sync(&ar_sdio->wr_async_work);

	ath6kl_core_cleanup(ar_sdio->ar);
	ath6kl_core_destroy(ar_sdio->ar);

	kfree(ar_sdio->dma_buffer);
	kfree(ar_sdio);
}