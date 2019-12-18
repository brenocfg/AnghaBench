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
typedef  int /*<<< orphan*/  u8 ;
struct bgx {int /*<<< orphan*/ * lmac; } ;

/* Variables and functions */
 int BGX_XCAST_BCAST_ACCEPT ; 
 int BGX_XCAST_MCAST_ACCEPT ; 
 int /*<<< orphan*/  bgx_flush_dmac_cam_filter (struct bgx*,int) ; 
 int /*<<< orphan*/  bgx_lmac_remove_filters (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_set_xcast_mode (int,int,int,int) ; 
 struct bgx* get_bgx (int,int) ; 

void bgx_reset_xcast_mode(int node, int bgx_idx, int lmacid, u8 vf_id)
{
	struct bgx *bgx = get_bgx(node, bgx_idx);

	if (!bgx)
		return;

	bgx_lmac_remove_filters(&bgx->lmac[lmacid], vf_id);
	bgx_flush_dmac_cam_filter(bgx, lmacid);
	bgx_set_xcast_mode(node, bgx_idx, lmacid,
			   (BGX_XCAST_BCAST_ACCEPT | BGX_XCAST_MCAST_ACCEPT));
}