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
typedef  int u32 ;
struct mt7530_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7530_PMCR_P (int) ; 
 int PMCR_RX_EN ; 
 int PMCR_TX_EN ; 
 int /*<<< orphan*/  mt7530_clear (struct mt7530_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt7530_set (struct mt7530_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mt7530_port_set_status(struct mt7530_priv *priv, int port, int enable)
{
	u32 mask = PMCR_TX_EN | PMCR_RX_EN;

	if (enable)
		mt7530_set(priv, MT7530_PMCR_P(port), mask);
	else
		mt7530_clear(priv, MT7530_PMCR_P(port), mask);
}