#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct bgx {TYPE_1__* lmac; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct bgx* get_bgx (int,int) ; 

void bgx_set_lmac_mac(int node, int bgx_idx, int lmacid, const u8 *mac)
{
	struct bgx *bgx = get_bgx(node, bgx_idx);

	if (!bgx)
		return;

	ether_addr_copy(bgx->lmac[lmacid].mac, mac);
}