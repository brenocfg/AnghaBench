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
struct pblk {int /*<<< orphan*/  rwb; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int mw_cunits; int all_luns; int ws_opt; int /*<<< orphan*/  csecs; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;

/* Variables and functions */
 int max (int,int) ; 
 int pblk_rb_init (int /*<<< orphan*/ *,unsigned long,int,int /*<<< orphan*/ ) ; 
 int write_buffer_size ; 

__attribute__((used)) static int pblk_rwb_init(struct pblk *pblk)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	unsigned long buffer_size;
	int pgs_in_buffer, threshold;

	threshold = geo->mw_cunits * geo->all_luns;
	pgs_in_buffer = (max(geo->mw_cunits, geo->ws_opt) + geo->ws_opt)
								* geo->all_luns;

	if (write_buffer_size && (write_buffer_size > pgs_in_buffer))
		buffer_size = write_buffer_size;
	else
		buffer_size = pgs_in_buffer;

	return pblk_rb_init(&pblk->rwb, buffer_size, threshold, geo->csecs);
}