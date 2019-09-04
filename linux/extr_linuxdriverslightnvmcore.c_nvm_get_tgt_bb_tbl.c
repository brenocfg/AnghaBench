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
typedef  int /*<<< orphan*/  u8 ;
struct ppa_addr {int dummy; } ;
struct nvm_tgt_dev {struct nvm_dev* parent; } ;
struct nvm_dev {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_bb_tbl ) (struct nvm_dev*,struct ppa_addr,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvm_ppa_tgt_to_dev (struct nvm_tgt_dev*,struct ppa_addr*,int) ; 
 int stub1 (struct nvm_dev*,struct ppa_addr,int /*<<< orphan*/ *) ; 

int nvm_get_tgt_bb_tbl(struct nvm_tgt_dev *tgt_dev, struct ppa_addr ppa,
		       u8 *blks)
{
	struct nvm_dev *dev = tgt_dev->parent;

	nvm_ppa_tgt_to_dev(tgt_dev, &ppa, 1);

	return dev->ops->get_bb_tbl(dev, ppa, blks);
}