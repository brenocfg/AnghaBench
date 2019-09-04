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
struct pblk {struct nvm_tgt_dev* dev; } ;
struct nvm_geo {scalar_t__ version; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;

/* Variables and functions */
 scalar_t__ NVM_OCSSD_SPEC_12 ; 
 void* pblk_bb_get_meta (struct pblk*) ; 
 void* pblk_chunk_get_info (struct pblk*) ; 

__attribute__((used)) static void *pblk_chunk_get_meta(struct pblk *pblk)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;

	if (geo->version == NVM_OCSSD_SPEC_12)
		return pblk_bb_get_meta(pblk);
	else
		return pblk_chunk_get_info(pblk);
}