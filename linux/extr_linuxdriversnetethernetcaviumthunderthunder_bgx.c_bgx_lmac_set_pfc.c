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
typedef  int u64 ;
struct pfc {scalar_t__ fc_tx; scalar_t__ fc_rx; } ;
struct lmac {scalar_t__ is_sgmii; } ;
struct bgx {struct lmac* lmac; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGX_SMUX_CBFC_CTL ; 
 int RX_EN ; 
 int TX_EN ; 
 int bgx_reg_read (struct bgx*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_reg_write (struct bgx*,int,int /*<<< orphan*/ ,int) ; 
 struct bgx* get_bgx (int,int) ; 

void bgx_lmac_set_pfc(int node, int bgx_idx, int lmacid, void *pause)
{
	struct pfc *pfc = (struct pfc *)pause;
	struct bgx *bgx = get_bgx(node, bgx_idx);
	struct lmac *lmac;
	u64 cfg;

	if (!bgx)
		return;
	lmac = &bgx->lmac[lmacid];
	if (lmac->is_sgmii)
		return;

	cfg = bgx_reg_read(bgx, lmacid, BGX_SMUX_CBFC_CTL);
	cfg &= ~(RX_EN | TX_EN);
	cfg |= (pfc->fc_rx ? RX_EN : 0x00);
	cfg |= (pfc->fc_tx ? TX_EN : 0x00);
	bgx_reg_write(bgx, lmacid, BGX_SMUX_CBFC_CTL, cfg);
}