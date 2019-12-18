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
typedef  int u8 ;
struct mrf24j40 {int /*<<< orphan*/  regmap_short; } ;
struct ieee802154_hw {struct mrf24j40* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TXMCR ; 
 int TXMCR_CSMA_RETRIES_MASK ; 
 int TXMCR_CSMA_RETRIES_SHIFT ; 
 int TXMCR_MIN_BE_MASK ; 
 int TXMCR_MIN_BE_SHIFT ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
mrf24j40_csma_params(struct ieee802154_hw *hw, u8 min_be, u8 max_be,
		     u8 retries)
{
	struct mrf24j40 *devrec = hw->priv;
	u8 val;

	/* min_be */
	val = min_be << TXMCR_MIN_BE_SHIFT;
	/* csma backoffs */
	val |= retries << TXMCR_CSMA_RETRIES_SHIFT;

	return regmap_update_bits(devrec->regmap_short, REG_TXMCR,
				  TXMCR_MIN_BE_MASK | TXMCR_CSMA_RETRIES_MASK,
				  val);
}