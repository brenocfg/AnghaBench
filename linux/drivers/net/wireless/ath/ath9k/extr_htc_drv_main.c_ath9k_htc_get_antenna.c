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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct base_eep_header {int /*<<< orphan*/  rxMask; int /*<<< orphan*/  txMask; } ;
struct ath9k_htc_priv {int dummy; } ;

/* Variables and functions */
 struct base_eep_header* ath9k_htc_get_eeprom_base (struct ath9k_htc_priv*) ; 

__attribute__((used)) static int ath9k_htc_get_antenna(struct ieee80211_hw *hw, u32 *tx_ant,
				 u32 *rx_ant)
{
	struct ath9k_htc_priv *priv = hw->priv;
	struct base_eep_header *pBase = ath9k_htc_get_eeprom_base(priv);
	if (pBase) {
		*tx_ant = pBase->txMask;
		*rx_ant = pBase->rxMask;
	} else {
		*tx_ant = 0;
		*rx_ant = 0;
	}
	return 0;
}