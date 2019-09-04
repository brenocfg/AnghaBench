#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct TYPE_6__ {unsigned int grp; unsigned int pu; unsigned int chk; unsigned int sec; } ;
struct TYPE_5__ {unsigned int ch; unsigned int lun; unsigned int blk; unsigned int pg; unsigned int pl; unsigned int sec; } ;
struct TYPE_4__ {unsigned int line; scalar_t__ is_cached; } ;
struct ppa_addr {scalar_t__ ppa; TYPE_3__ m; TYPE_2__ g; TYPE_1__ c; } ;
struct nvm_addrf {unsigned int ch_offset; unsigned int lun_offset; unsigned int chk_offset; unsigned int sec_offset; } ;
struct pblk {struct nvm_addrf addrf; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {scalar_t__ version; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_addrf_12 {unsigned int ch_offset; unsigned int lun_offset; unsigned int blk_offset; unsigned int pg_offset; unsigned int pln_offset; unsigned int sec_offset; } ;

/* Variables and functions */
 scalar_t__ ADDR_EMPTY ; 
 scalar_t__ NVM_OCSSD_SPEC_12 ; 

__attribute__((used)) static inline u32 pblk_ppa64_to_ppa32(struct pblk *pblk, struct ppa_addr ppa64)
{
	u32 ppa32 = 0;

	if (ppa64.ppa == ADDR_EMPTY) {
		ppa32 = ~0U;
	} else if (ppa64.c.is_cached) {
		ppa32 |= ppa64.c.line;
		ppa32 |= 1U << 31;
	} else {
		struct nvm_tgt_dev *dev = pblk->dev;
		struct nvm_geo *geo = &dev->geo;

		if (geo->version == NVM_OCSSD_SPEC_12) {
			struct nvm_addrf_12 *ppaf =
					(struct nvm_addrf_12 *)&pblk->addrf;

			ppa32 |= ppa64.g.ch << ppaf->ch_offset;
			ppa32 |= ppa64.g.lun << ppaf->lun_offset;
			ppa32 |= ppa64.g.blk << ppaf->blk_offset;
			ppa32 |= ppa64.g.pg << ppaf->pg_offset;
			ppa32 |= ppa64.g.pl << ppaf->pln_offset;
			ppa32 |= ppa64.g.sec << ppaf->sec_offset;
		} else {
			struct nvm_addrf *lbaf = &pblk->addrf;

			ppa32 |= ppa64.m.grp << lbaf->ch_offset;
			ppa32 |= ppa64.m.pu << lbaf->lun_offset;
			ppa32 |= ppa64.m.chk << lbaf->chk_offset;
			ppa32 |= ppa64.m.sec << lbaf->sec_offset;
		}
	}

	return ppa32;
}