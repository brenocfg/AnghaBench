#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct rvu {TYPE_1__* hw; } ;
struct TYPE_4__ {int max; } ;
struct npc_pkind {int* pfchan_map; TYPE_2__ rsrc; } ;
struct TYPE_3__ {struct npc_pkind pkind; } ;

/* Variables and functions */

int rvu_npc_get_pkind(struct rvu *rvu, u16 pf)
{
	struct npc_pkind *pkind = &rvu->hw->pkind;
	u32 map;
	int i;

	for (i = 0; i < pkind->rsrc.max; i++) {
		map = pkind->pfchan_map[i];
		if (((map >> 16) & 0x3F) == pf)
			return i;
	}
	return -1;
}