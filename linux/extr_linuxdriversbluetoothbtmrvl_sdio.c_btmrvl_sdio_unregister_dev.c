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
struct btmrvl_sdio_card {scalar_t__ func; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdio_claim_host (scalar_t__) ; 
 int /*<<< orphan*/  sdio_disable_func (scalar_t__) ; 
 int /*<<< orphan*/  sdio_release_host (scalar_t__) ; 
 int /*<<< orphan*/  sdio_release_irq (scalar_t__) ; 
 int /*<<< orphan*/  sdio_set_drvdata (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btmrvl_sdio_unregister_dev(struct btmrvl_sdio_card *card)
{
	if (card && card->func) {
		sdio_claim_host(card->func);
		sdio_release_irq(card->func);
		sdio_disable_func(card->func);
		sdio_release_host(card->func);
		sdio_set_drvdata(card->func, NULL);
	}

	return 0;
}