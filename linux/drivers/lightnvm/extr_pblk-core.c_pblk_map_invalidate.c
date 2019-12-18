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
struct ppa_addr {int dummy; } ;
struct pblk_line {int dummy; } ;
struct pblk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pblk_map_invalidate (struct pblk*,struct pblk_line*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_addr_in_cache (struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_dev_ppa_to_line_addr (struct pblk*,struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_ppa_empty (struct ppa_addr) ; 
 struct pblk_line* pblk_ppa_to_line (struct pblk*,struct ppa_addr) ; 

void pblk_map_invalidate(struct pblk *pblk, struct ppa_addr ppa)
{
	struct pblk_line *line;
	u64 paddr;

#ifdef CONFIG_NVM_PBLK_DEBUG
	/* Callers must ensure that the ppa points to a device address */
	BUG_ON(pblk_addr_in_cache(ppa));
	BUG_ON(pblk_ppa_empty(ppa));
#endif

	line = pblk_ppa_to_line(pblk, ppa);
	paddr = pblk_dev_ppa_to_line_addr(pblk, ppa);

	__pblk_map_invalidate(pblk, line, paddr);
}