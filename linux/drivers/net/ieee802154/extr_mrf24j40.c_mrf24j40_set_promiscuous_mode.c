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
 int BIT_ERRPKT ; 
 int BIT_NOACKRSP ; 
 int BIT_PROMI ; 
 int /*<<< orphan*/  REG_RXMCR ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mrf24j40_set_promiscuous_mode(struct ieee802154_hw *hw, bool on)
{
	struct mrf24j40 *devrec = hw->priv;
	int ret;

	if (on) {
		/* set PROMI, ERRPKT and NOACKRSP */
		ret = regmap_update_bits(devrec->regmap_short, REG_RXMCR,
					 BIT_PROMI | BIT_ERRPKT | BIT_NOACKRSP,
					 BIT_PROMI | BIT_ERRPKT | BIT_NOACKRSP);
	} else {
		/* clear PROMI, ERRPKT and NOACKRSP */
		ret = regmap_update_bits(devrec->regmap_short, REG_RXMCR,
					 BIT_PROMI | BIT_ERRPKT | BIT_NOACKRSP,
					 0);
	}

	return ret;
}