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
struct nvm_addrf {int ch_offset; int ch_len; int lun_offset; int lun_len; int chk_offset; int chk_len; int sec_offset; int sec_len; } ;
struct pblk {int addrf_len; struct nvm_addrf addrf; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {scalar_t__ version; struct nvm_addrf addrf; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_addrf_12 {int blk_offset; int blk_len; int pg_offset; int pg_len; int lun_offset; int lun_len; int ch_offset; int ch_len; int pln_offset; int pln_len; int sec_offset; int sec_len; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ NVM_OCSSD_SPEC_12 ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ snprintf (char*,scalar_t__,char*,int,int,int,int,int,int,int,int,...) ; 

__attribute__((used)) static ssize_t pblk_sysfs_ppaf(struct pblk *pblk, char *page)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	ssize_t sz = 0;

	if (geo->version == NVM_OCSSD_SPEC_12) {
		struct nvm_addrf_12 *ppaf = (struct nvm_addrf_12 *)&pblk->addrf;
		struct nvm_addrf_12 *gppaf = (struct nvm_addrf_12 *)&geo->addrf;

		sz = snprintf(page, PAGE_SIZE,
			"g:(b:%d)blk:%d/%d,pg:%d/%d,lun:%d/%d,ch:%d/%d,pl:%d/%d,sec:%d/%d\n",
			pblk->addrf_len,
			ppaf->blk_offset, ppaf->blk_len,
			ppaf->pg_offset, ppaf->pg_len,
			ppaf->lun_offset, ppaf->lun_len,
			ppaf->ch_offset, ppaf->ch_len,
			ppaf->pln_offset, ppaf->pln_len,
			ppaf->sec_offset, ppaf->sec_len);

		sz += snprintf(page + sz, PAGE_SIZE - sz,
			"d:blk:%d/%d,pg:%d/%d,lun:%d/%d,ch:%d/%d,pl:%d/%d,sec:%d/%d\n",
			gppaf->blk_offset, gppaf->blk_len,
			gppaf->pg_offset, gppaf->pg_len,
			gppaf->lun_offset, gppaf->lun_len,
			gppaf->ch_offset, gppaf->ch_len,
			gppaf->pln_offset, gppaf->pln_len,
			gppaf->sec_offset, gppaf->sec_len);
	} else {
		struct nvm_addrf *ppaf = &pblk->addrf;
		struct nvm_addrf *gppaf = &geo->addrf;

		sz = snprintf(page, PAGE_SIZE,
			"pblk:(s:%d)ch:%d/%d,lun:%d/%d,chk:%d/%d/sec:%d/%d\n",
			pblk->addrf_len,
			ppaf->ch_offset, ppaf->ch_len,
			ppaf->lun_offset, ppaf->lun_len,
			ppaf->chk_offset, ppaf->chk_len,
			ppaf->sec_offset, ppaf->sec_len);

		sz += snprintf(page + sz, PAGE_SIZE - sz,
			"device:ch:%d/%d,lun:%d/%d,chk:%d/%d,sec:%d/%d\n",
			gppaf->ch_offset, gppaf->ch_len,
			gppaf->lun_offset, gppaf->lun_len,
			gppaf->chk_offset, gppaf->chk_len,
			gppaf->sec_offset, gppaf->sec_len);
	}

	return sz;
}