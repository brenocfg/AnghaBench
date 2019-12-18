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
struct ll_disk {int (* open_index ) (struct ll_disk*) ;void* ref_count_root; void* bitmap_root; void* nr_allocated; void* nr_blocks; int /*<<< orphan*/  commit; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  init_index; int /*<<< orphan*/  save_ie; int /*<<< orphan*/  load_ie; } ;
struct dm_transaction_manager {int dummy; } ;
struct disk_sm_root {int /*<<< orphan*/  ref_count_root; int /*<<< orphan*/  bitmap_root; int /*<<< orphan*/  nr_allocated; int /*<<< orphan*/  nr_blocks; } ;
typedef  int /*<<< orphan*/  smr ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int ENOMEM ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct disk_sm_root*,void*,int) ; 
 int /*<<< orphan*/  metadata_ll_commit ; 
 int /*<<< orphan*/  metadata_ll_init_index ; 
 int /*<<< orphan*/  metadata_ll_load_ie ; 
 int /*<<< orphan*/  metadata_ll_max_entries ; 
 int metadata_ll_open (struct ll_disk*) ; 
 int /*<<< orphan*/  metadata_ll_save_ie ; 
 int sm_ll_init (struct ll_disk*,struct dm_transaction_manager*) ; 
 int stub1 (struct ll_disk*) ; 

int sm_ll_open_metadata(struct ll_disk *ll, struct dm_transaction_manager *tm,
			void *root_le, size_t len)
{
	int r;
	struct disk_sm_root smr;

	if (len < sizeof(struct disk_sm_root)) {
		DMERR("sm_metadata root too small");
		return -ENOMEM;
	}

	/*
	 * We don't know the alignment of the root_le buffer, so need to
	 * copy into a new structure.
	 */
	memcpy(&smr, root_le, sizeof(smr));

	r = sm_ll_init(ll, tm);
	if (r < 0)
		return r;

	ll->load_ie = metadata_ll_load_ie;
	ll->save_ie = metadata_ll_save_ie;
	ll->init_index = metadata_ll_init_index;
	ll->open_index = metadata_ll_open;
	ll->max_entries = metadata_ll_max_entries;
	ll->commit = metadata_ll_commit;

	ll->nr_blocks = le64_to_cpu(smr.nr_blocks);
	ll->nr_allocated = le64_to_cpu(smr.nr_allocated);
	ll->bitmap_root = le64_to_cpu(smr.bitmap_root);
	ll->ref_count_root = le64_to_cpu(smr.ref_count_root);

	return ll->open_index(ll);
}