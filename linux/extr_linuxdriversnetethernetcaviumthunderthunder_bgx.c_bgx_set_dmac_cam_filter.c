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
typedef  int /*<<< orphan*/  u64 ;
struct lmac {int /*<<< orphan*/  mac; } ;
struct bgx {struct lmac* lmac; } ;

/* Variables and functions */
 int /*<<< orphan*/  bgx_lmac_save_filter (struct lmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_to_u64 (int /*<<< orphan*/ ) ; 
 struct bgx* get_bgx (int,int) ; 

void bgx_set_dmac_cam_filter(int node, int bgx_idx, int lmacid,
			     u64 cam_dmac, u8 vf_id)
{
	struct bgx *bgx = get_bgx(node, bgx_idx);
	struct lmac *lmac = NULL;

	if (!bgx)
		return;

	lmac = &bgx->lmac[lmacid];

	if (!cam_dmac)
		cam_dmac = ether_addr_to_u64(lmac->mac);

	/* since we might have several VFs attached to particular LMAC
	 * and kernel could call mcast config for each of them with the
	 * same MAC, check if requested MAC is already in filtering list and
	 * updare/prepare list of MACs to be applied later to HW filters
	 */
	bgx_lmac_save_filter(lmac, cam_dmac, vf_id);
}