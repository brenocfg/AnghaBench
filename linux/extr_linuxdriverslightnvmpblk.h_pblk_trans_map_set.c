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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ppa_addr {int /*<<< orphan*/  ppa; } ;
struct pblk {int addrf_len; scalar_t__ trans_map; } ;
typedef  size_t sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  pblk_ppa64_to_ppa32 (struct pblk*,struct ppa_addr) ; 

__attribute__((used)) static inline void pblk_trans_map_set(struct pblk *pblk, sector_t lba,
						struct ppa_addr ppa)
{
	if (pblk->addrf_len < 32) {
		u32 *map = (u32 *)pblk->trans_map;

		map[lba] = pblk_ppa64_to_ppa32(pblk, ppa);
	} else {
		u64 *map = (u64 *)pblk->trans_map;

		map[lba] = ppa.ppa;
	}
}