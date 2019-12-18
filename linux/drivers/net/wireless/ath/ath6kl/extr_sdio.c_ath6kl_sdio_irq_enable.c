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
struct ath6kl_sdio {int /*<<< orphan*/  func; } ;
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 
 int /*<<< orphan*/  ath6kl_sdio_irq_handler ; 
 struct ath6kl_sdio* ath6kl_sdio_priv (struct ath6kl*) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int sdio_claim_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath6kl_sdio_irq_enable(struct ath6kl *ar)
{
	struct ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	int ret;

	sdio_claim_host(ar_sdio->func);

	/* Register the isr */
	ret =  sdio_claim_irq(ar_sdio->func, ath6kl_sdio_irq_handler);
	if (ret)
		ath6kl_err("Failed to claim sdio irq: %d\n", ret);

	sdio_release_host(ar_sdio->func);
}