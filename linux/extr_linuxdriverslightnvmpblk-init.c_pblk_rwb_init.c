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
struct pblk_rb_entry {int dummy; } ;
struct pblk {int /*<<< orphan*/  rwb; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int all_luns; unsigned long csecs; int /*<<< orphan*/  ws_opt; int /*<<< orphan*/  mw_cunits; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  array_size (unsigned long,int) ; 
 unsigned int get_count_order (unsigned long) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long pblk_rb_calculate_size (unsigned long) ; 
 int pblk_rb_init (int /*<<< orphan*/ *,struct pblk_rb_entry*,unsigned int,unsigned int) ; 
 struct pblk_rb_entry* vzalloc (int /*<<< orphan*/ ) ; 
 int write_buffer_size ; 

__attribute__((used)) static int pblk_rwb_init(struct pblk *pblk)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_rb_entry *entries;
	unsigned long nr_entries, buffer_size;
	unsigned int power_size, power_seg_sz;
	int pgs_in_buffer;

	pgs_in_buffer = max(geo->mw_cunits, geo->ws_opt) * geo->all_luns;

	if (write_buffer_size && (write_buffer_size > pgs_in_buffer))
		buffer_size = write_buffer_size;
	else
		buffer_size = pgs_in_buffer;

	nr_entries = pblk_rb_calculate_size(buffer_size);

	entries = vzalloc(array_size(nr_entries, sizeof(struct pblk_rb_entry)));
	if (!entries)
		return -ENOMEM;

	power_size = get_count_order(nr_entries);
	power_seg_sz = get_count_order(geo->csecs);

	return pblk_rb_init(&pblk->rwb, entries, power_size, power_seg_sz);
}