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
typedef  int /*<<< orphan*/  u32 ;
struct ppa_addr {int dummy; } ;
struct pblk {int addrf_len; scalar_t__ trans_map; } ;
typedef  size_t sector_t ;

/* Variables and functions */
 struct ppa_addr pblk_ppa32_to_ppa64 (struct pblk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ppa_addr pblk_trans_map_get(struct pblk *pblk,
								sector_t lba)
{
	struct ppa_addr ppa;

	if (pblk->addrf_len < 32) {
		u32 *map = (u32 *)pblk->trans_map;

		ppa = pblk_ppa32_to_ppa64(pblk, map[lba]);
	} else {
		struct ppa_addr *map = (struct ppa_addr *)pblk->trans_map;

		ppa = map[lba];
	}

	return ppa;
}