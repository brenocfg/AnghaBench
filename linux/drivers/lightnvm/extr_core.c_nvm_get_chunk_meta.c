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
struct ppa_addr {scalar_t__ ppa; } ;
struct nvm_tgt_dev {struct nvm_dev* parent; } ;
struct TYPE_3__ {scalar_t__ version; } ;
struct nvm_dev {TYPE_2__* ops; TYPE_1__ geo; } ;
struct nvm_chk_meta {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_4__ {int (* get_chk_meta ) (struct nvm_dev*,int /*<<< orphan*/ ,int,struct nvm_chk_meta*) ;} ;

/* Variables and functions */
 scalar_t__ NVM_OCSSD_SPEC_12 ; 
 int nvm_get_bb_meta (struct nvm_dev*,int /*<<< orphan*/ ,int,struct nvm_chk_meta*) ; 
 int /*<<< orphan*/  nvm_ppa_tgt_to_dev (struct nvm_tgt_dev*,struct ppa_addr*,int) ; 
 int stub1 (struct nvm_dev*,int /*<<< orphan*/ ,int,struct nvm_chk_meta*) ; 

int nvm_get_chunk_meta(struct nvm_tgt_dev *tgt_dev, struct ppa_addr ppa,
		       int nchks, struct nvm_chk_meta *meta)
{
	struct nvm_dev *dev = tgt_dev->parent;

	nvm_ppa_tgt_to_dev(tgt_dev, &ppa, 1);

	if (dev->geo.version == NVM_OCSSD_SPEC_12)
		return nvm_get_bb_meta(dev, (sector_t)ppa.ppa, nchks, meta);

	return dev->ops->get_chk_meta(dev, (sector_t)ppa.ppa, nchks, meta);
}