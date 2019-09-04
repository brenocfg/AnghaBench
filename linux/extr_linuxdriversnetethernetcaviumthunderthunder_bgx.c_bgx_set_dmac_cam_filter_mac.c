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
typedef  int u64 ;
struct lmac {int dmacs_count; } ;
struct bgx {struct lmac* lmac; } ;

/* Variables and functions */
 scalar_t__ BGX_CMR_RX_DMACX_CAM ; 
 int LMAC_ID_MASK ; 
 int RX_DMACX_CAM_EN ; 
 int RX_DMACX_CAM_LMACID (int) ; 
 int /*<<< orphan*/  bgx_reg_write (struct bgx*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int bgx_set_dmac_cam_filter_mac(struct bgx *bgx, int lmacid,
				       u64 cam_dmac, u8 idx)
{
	struct lmac *lmac = NULL;
	u64 cfg = 0;

	/* skip zero addresses as meaningless */
	if (!cam_dmac || !bgx)
		return -1;

	lmac = &bgx->lmac[lmacid];

	/* configure DCAM filtering for designated LMAC */
	cfg = RX_DMACX_CAM_LMACID(lmacid & LMAC_ID_MASK) |
		RX_DMACX_CAM_EN | cam_dmac;
	bgx_reg_write(bgx, 0, BGX_CMR_RX_DMACX_CAM +
		      ((lmacid * lmac->dmacs_count) + idx) * sizeof(u64), cfg);
	return 0;
}