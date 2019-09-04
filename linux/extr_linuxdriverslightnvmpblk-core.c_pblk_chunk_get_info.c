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
struct ppa_addr {scalar_t__ ppa; } ;
struct pblk {struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int all_chunks; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_chk_meta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct nvm_chk_meta* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct nvm_chk_meta*) ; 
 struct nvm_chk_meta* kzalloc (unsigned long,int /*<<< orphan*/ ) ; 
 int nvm_get_chunk_meta (struct nvm_tgt_dev*,struct nvm_chk_meta*,struct ppa_addr,int) ; 

struct nvm_chk_meta *pblk_chunk_get_info(struct pblk *pblk)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct nvm_chk_meta *meta;
	struct ppa_addr ppa;
	unsigned long len;
	int ret;

	ppa.ppa = 0;

	len = geo->all_chunks * sizeof(*meta);
	meta = kzalloc(len, GFP_KERNEL);
	if (!meta)
		return ERR_PTR(-ENOMEM);

	ret = nvm_get_chunk_meta(dev, meta, ppa, geo->all_chunks);
	if (ret) {
		kfree(meta);
		return ERR_PTR(-EIO);
	}

	return meta;
}