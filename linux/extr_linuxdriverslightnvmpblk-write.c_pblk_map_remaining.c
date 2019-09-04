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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {scalar_t__ sec; } ;
struct TYPE_4__ {scalar_t__ pg; } ;
struct ppa_addr {TYPE_2__ m; TYPE_1__ g; int /*<<< orphan*/  ppa; } ;
struct pblk_line {int /*<<< orphan*/  lock; TYPE_3__* w_err_gc; int /*<<< orphan*/  vsc; int /*<<< orphan*/  invalid_bitmap; int /*<<< orphan*/  left_msecs; int /*<<< orphan*/  map_bitmap; } ;
struct pblk {struct pblk_line* lines; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {scalar_t__ version; scalar_t__ num_pg; scalar_t__ clba; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct TYPE_6__ {int has_write_err; } ;

/* Variables and functions */
 scalar_t__ NVM_OCSSD_SPEC_12 ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pblk_dev_ppa_to_line_addr (struct pblk*,struct ppa_addr) ; 
 size_t pblk_ppa_to_line (struct ppa_addr) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pblk_map_remaining(struct pblk *pblk, struct ppa_addr *ppa)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_line *line;
	struct ppa_addr map_ppa = *ppa;
	u64 paddr;
	int done = 0;

	line = &pblk->lines[pblk_ppa_to_line(*ppa)];
	spin_lock(&line->lock);

	while (!done)  {
		paddr = pblk_dev_ppa_to_line_addr(pblk, map_ppa);

		if (!test_and_set_bit(paddr, line->map_bitmap))
			line->left_msecs--;

		if (!test_and_set_bit(paddr, line->invalid_bitmap))
			le32_add_cpu(line->vsc, -1);

		if (geo->version == NVM_OCSSD_SPEC_12) {
			map_ppa.ppa++;
			if (map_ppa.g.pg == geo->num_pg)
				done = 1;
		} else {
			map_ppa.m.sec++;
			if (map_ppa.m.sec == geo->clba)
				done = 1;
		}
	}

	line->w_err_gc->has_write_err = 1;
	spin_unlock(&line->lock);
}