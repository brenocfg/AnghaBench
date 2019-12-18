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
struct ppa_addr {int dummy; } ;
struct pblk_lun {struct ppa_addr bppa; } ;
struct pblk_line {struct nvm_chk_meta* chks; } ;
struct pblk {struct pblk_lun* luns; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int dummy; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_chk_meta {int dummy; } ;

/* Variables and functions */
 int pblk_ppa_to_pos (struct nvm_geo*,struct ppa_addr) ; 

__attribute__((used)) static struct nvm_chk_meta *pblk_get_stripe_chunk(struct pblk *pblk,
						  struct pblk_line *line,
						  int index)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_lun *rlun;
	struct ppa_addr ppa;
	int pos;

	rlun = &pblk->luns[index];
	ppa = rlun->bppa;
	pos = pblk_ppa_to_pos(geo, ppa);

	return &line->chks[pos];
}