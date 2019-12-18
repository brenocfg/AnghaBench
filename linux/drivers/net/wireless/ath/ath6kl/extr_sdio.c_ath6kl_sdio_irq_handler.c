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
struct sdio_func {int dummy; } ;
struct ath6kl_sdio {int /*<<< orphan*/  irq_wq; int /*<<< orphan*/  irq_handling; int /*<<< orphan*/  func; int /*<<< orphan*/  ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_SDIO ; 
 int ECANCELED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*) ; 
 int ath6kl_hif_intr_bh_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 struct ath6kl_sdio* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath6kl_sdio_irq_handler(struct sdio_func *func)
{
	int status;
	struct ath6kl_sdio *ar_sdio;

	ath6kl_dbg(ATH6KL_DBG_SDIO, "irq\n");

	ar_sdio = sdio_get_drvdata(func);
	atomic_set(&ar_sdio->irq_handling, 1);
	/*
	 * Release the host during interrups so we can pick it back up when
	 * we process commands.
	 */
	sdio_release_host(ar_sdio->func);

	status = ath6kl_hif_intr_bh_handler(ar_sdio->ar);
	sdio_claim_host(ar_sdio->func);

	atomic_set(&ar_sdio->irq_handling, 0);
	wake_up(&ar_sdio->irq_wq);

	WARN_ON(status && status != -ECANCELED);
}