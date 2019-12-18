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
typedef  int u8 ;
struct mrf24j40 {int* irq_buf; int /*<<< orphan*/  tx_skb; int /*<<< orphan*/  hw; int /*<<< orphan*/  regmap_short; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int BIT_RXIF ; 
 int BIT_SECIF ; 
 int /*<<< orphan*/  BIT_SECIGNORE ; 
 int BIT_TXNIF ; 
 int /*<<< orphan*/  REG_SECCON0 ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_xmit_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrf24j40_handle_rx (struct mrf24j40*) ; 
 int /*<<< orphan*/  regmap_write_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mrf24j40_intstat_complete(void *context)
{
	struct mrf24j40 *devrec = context;
	u8 intstat = devrec->irq_buf[1];

	enable_irq(devrec->spi->irq);

	/* Ignore Rx security decryption */
	if (intstat & BIT_SECIF)
		regmap_write_async(devrec->regmap_short, REG_SECCON0,
				   BIT_SECIGNORE);

	/* Check for TX complete */
	if (intstat & BIT_TXNIF)
		ieee802154_xmit_complete(devrec->hw, devrec->tx_skb, false);

	/* Check for Rx */
	if (intstat & BIT_RXIF)
		mrf24j40_handle_rx(devrec);
}