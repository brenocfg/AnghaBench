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
struct ieee802154_hw {struct cc2520_private* priv; } ;
struct cc2520_private {int /*<<< orphan*/  amplified; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int cc2520_cc2591_set_tx_power (struct cc2520_private*,int /*<<< orphan*/ ) ; 
 int cc2520_set_tx_power (struct cc2520_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cc2520_set_txpower(struct ieee802154_hw *hw, s32 mbm)
{
	struct cc2520_private *priv = hw->priv;

	if (!priv->amplified)
		return cc2520_set_tx_power(priv, mbm);

	return cc2520_cc2591_set_tx_power(priv, mbm);
}