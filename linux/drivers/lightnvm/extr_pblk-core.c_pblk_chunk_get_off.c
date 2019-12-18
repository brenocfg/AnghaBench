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
struct TYPE_2__ {int grp; int pu; int chk; } ;
struct ppa_addr {TYPE_1__ m; } ;
struct pblk {struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int num_chk; int num_lun; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_chk_meta {int dummy; } ;

/* Variables and functions */

struct nvm_chk_meta *pblk_chunk_get_off(struct pblk *pblk,
					      struct nvm_chk_meta *meta,
					      struct ppa_addr ppa)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	int ch_off = ppa.m.grp * geo->num_chk * geo->num_lun;
	int lun_off = ppa.m.pu * geo->num_chk;
	int chk_off = ppa.m.chk;

	return meta + ch_off + lun_off + chk_off;
}