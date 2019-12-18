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
struct lmac {int /*<<< orphan*/  last_speed; int /*<<< orphan*/  last_duplex; int /*<<< orphan*/  link_up; int /*<<< orphan*/  lmac_type; } ;
struct bgx_link_status {int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; int /*<<< orphan*/  link_up; int /*<<< orphan*/  mac_type; } ;
struct bgx {struct lmac* lmac; } ;

/* Variables and functions */
 struct bgx* get_bgx (int,int) ; 

void bgx_get_lmac_link_state(int node, int bgx_idx, int lmacid, void *status)
{
	struct bgx_link_status *link = (struct bgx_link_status *)status;
	struct bgx *bgx;
	struct lmac *lmac;

	bgx = get_bgx(node, bgx_idx);
	if (!bgx)
		return;

	lmac = &bgx->lmac[lmacid];
	link->mac_type = lmac->lmac_type;
	link->link_up = lmac->link_up;
	link->duplex = lmac->last_duplex;
	link->speed = lmac->last_speed;
}