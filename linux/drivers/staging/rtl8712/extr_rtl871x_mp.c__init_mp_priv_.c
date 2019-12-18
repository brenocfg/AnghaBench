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
struct mp_priv {int curr_ch; int curr_txpoweridx; scalar_t__ rx_crcerrpktcount; scalar_t__ rx_pktcount; scalar_t__ tx_pktcount; scalar_t__ check_mp_pkt; int /*<<< orphan*/  antenna_rx; int /*<<< orphan*/  antenna_tx; scalar_t__ curr_rateidx; int /*<<< orphan*/  curr_modem; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANTENNA_A ; 
 int /*<<< orphan*/  ANTENNA_AB ; 
 int /*<<< orphan*/  MIXED_PHY ; 
 int /*<<< orphan*/  _LOOPBOOK_MODE_ ; 

__attribute__((used)) static void _init_mp_priv_(struct mp_priv *pmp_priv)
{
	pmp_priv->mode = _LOOPBOOK_MODE_;
	pmp_priv->curr_ch = 1;
	pmp_priv->curr_modem = MIXED_PHY;
	pmp_priv->curr_rateidx = 0;
	pmp_priv->curr_txpoweridx = 0x14;
	pmp_priv->antenna_tx = ANTENNA_A;
	pmp_priv->antenna_rx = ANTENNA_AB;
	pmp_priv->check_mp_pkt = 0;
	pmp_priv->tx_pktcount = 0;
	pmp_priv->rx_pktcount = 0;
	pmp_priv->rx_crcerrpktcount = 0;
}