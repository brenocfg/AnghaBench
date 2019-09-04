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
struct pblk {int /*<<< orphan*/  uaddrf; int /*<<< orphan*/  addrf; int /*<<< orphan*/  addrf_len; int /*<<< orphan*/  min_write_pgs; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int version; int /*<<< orphan*/  clba; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVM_OCSSD_SPEC_12 129 
#define  NVM_OCSSD_SPEC_20 128 
 int /*<<< orphan*/  div_u64_rem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,...) ; 
 int /*<<< orphan*/  pblk_set_addrf_12 (struct pblk*,struct nvm_geo*,void*) ; 
 int /*<<< orphan*/  pblk_set_addrf_20 (struct nvm_geo*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pblk_set_addrf(struct pblk *pblk)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	int mod;

	switch (geo->version) {
	case NVM_OCSSD_SPEC_12:
		div_u64_rem(geo->clba, pblk->min_write_pgs, &mod);
		if (mod) {
			pblk_err(pblk, "bad configuration of sectors/pages\n");
			return -EINVAL;
		}

		pblk->addrf_len = pblk_set_addrf_12(pblk, geo,
							(void *)&pblk->addrf);
		break;
	case NVM_OCSSD_SPEC_20:
		pblk->addrf_len = pblk_set_addrf_20(geo, (void *)&pblk->addrf,
							&pblk->uaddrf);
		break;
	default:
		pblk_err(pblk, "OCSSD revision not supported (%d)\n",
								geo->version);
		return -EINVAL;
	}

	return 0;
}