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
typedef  int u64 ;
struct TYPE_4__ {int sec; scalar_t__ pu; scalar_t__ grp; } ;
struct TYPE_3__ {scalar_t__ sec; scalar_t__ pl; scalar_t__ pg; scalar_t__ lun; scalar_t__ ch; } ;
struct ppa_addr {TYPE_2__ m; TYPE_1__ g; } ;
struct pblk_addrf {int sec_stripe; int sec_lun_stripe; int sec_ws_stripe; } ;
struct pblk {struct pblk_addrf uaddrf; int /*<<< orphan*/  addrf; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {scalar_t__ version; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_addrf_12 {int ch_offset; int lun_offset; int pg_offset; int pln_offset; int sec_offset; } ;

/* Variables and functions */
 scalar_t__ NVM_OCSSD_SPEC_12 ; 
 int div_u64_rem (int,int,int*) ; 

__attribute__((used)) static inline u64 pblk_dev_ppa_to_line_addr(struct pblk *pblk,
							struct ppa_addr p)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	u64 paddr;

	if (geo->version == NVM_OCSSD_SPEC_12) {
		struct nvm_addrf_12 *ppaf = (struct nvm_addrf_12 *)&pblk->addrf;

		paddr = (u64)p.g.ch << ppaf->ch_offset;
		paddr |= (u64)p.g.lun << ppaf->lun_offset;
		paddr |= (u64)p.g.pg << ppaf->pg_offset;
		paddr |= (u64)p.g.pl << ppaf->pln_offset;
		paddr |= (u64)p.g.sec << ppaf->sec_offset;
	} else {
		struct pblk_addrf *uaddrf = &pblk->uaddrf;
		u64 secs = p.m.sec;
		int sec_stripe;

		paddr = (u64)p.m.grp * uaddrf->sec_stripe;
		paddr += (u64)p.m.pu * uaddrf->sec_lun_stripe;

		secs = div_u64_rem(secs, uaddrf->sec_stripe, &sec_stripe);
		paddr += secs * uaddrf->sec_ws_stripe;
		paddr += sec_stripe;
	}

	return paddr;
}