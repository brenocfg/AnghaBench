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
struct nvm_geo {scalar_t__ version; int pln_mode; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;

/* Variables and functions */
 int NVM_IO_SCRAMBLE_ENABLE ; 
 scalar_t__ NVM_OCSSD_SPEC_20 ; 
 int PBLK_WRITE ; 

__attribute__((used)) static inline int pblk_set_progr_mode(struct pblk *pblk, int type)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	int flags;

	if (geo->version == NVM_OCSSD_SPEC_20)
		return 0;

	flags = geo->pln_mode >> 1;

	if (type == PBLK_WRITE)
		flags |= NVM_IO_SCRAMBLE_ENABLE;

	return flags;
}