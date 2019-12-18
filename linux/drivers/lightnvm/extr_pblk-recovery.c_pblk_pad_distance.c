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
struct pblk_line {int left_msecs; } ;
struct pblk {struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int mw_cunits; int all_luns; int ws_opt; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;

/* Variables and functions */

__attribute__((used)) static int pblk_pad_distance(struct pblk *pblk, struct pblk_line *line)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	int distance = geo->mw_cunits * geo->all_luns * geo->ws_opt;

	return (distance > line->left_msecs) ? line->left_msecs : distance;
}