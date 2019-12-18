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
struct mrf24j40 {int /*<<< orphan*/  regmap_short; } ;
struct ieee802154_hw {struct mrf24j40* priv; } ;

/* Variables and functions */
 int BIT_RXIE ; 
 int BIT_TXNIE ; 
 int /*<<< orphan*/  REG_INTCON ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printdev (struct mrf24j40*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void mrf24j40_stop(struct ieee802154_hw *hw)
{
	struct mrf24j40 *devrec = hw->priv;

	dev_dbg(printdev(devrec), "stop\n");

	/* Set TXNIE and RXIE. Disable Interrupts */
	regmap_update_bits(devrec->regmap_short, REG_INTCON,
			   BIT_TXNIE | BIT_RXIE, BIT_TXNIE | BIT_RXIE);
}