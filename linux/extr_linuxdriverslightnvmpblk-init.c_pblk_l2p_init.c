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
struct ppa_addr {int dummy; } ;
struct TYPE_2__ {scalar_t__ nr_secs; } ;
struct pblk {int /*<<< orphan*/  trans_map; TYPE_1__ rl; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int ENOMEM ; 
 int pblk_l2p_recover (struct pblk*,int) ; 
 int /*<<< orphan*/  pblk_ppa_set_empty (struct ppa_addr*) ; 
 int /*<<< orphan*/  pblk_trans_map_set (struct pblk*,scalar_t__,struct ppa_addr) ; 
 size_t pblk_trans_map_size (struct pblk*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc (size_t) ; 

__attribute__((used)) static int pblk_l2p_init(struct pblk *pblk, bool factory_init)
{
	sector_t i;
	struct ppa_addr ppa;
	size_t map_size;
	int ret = 0;

	map_size = pblk_trans_map_size(pblk);
	pblk->trans_map = vmalloc(map_size);
	if (!pblk->trans_map)
		return -ENOMEM;

	pblk_ppa_set_empty(&ppa);

	for (i = 0; i < pblk->rl.nr_secs; i++)
		pblk_trans_map_set(pblk, i, ppa);

	ret = pblk_l2p_recover(pblk, factory_init);
	if (ret)
		vfree(pblk->trans_map);

	return ret;
}