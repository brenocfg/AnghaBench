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

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  disk_ll_commit ; 
 int /*<<< orphan*/  disk_ll_init_index ; 
 int /*<<< orphan*/  disk_ll_load_ie ; 
 int /*<<< orphan*/  disk_ll_max_entries ; 
 int disk_ll_open (struct ll_disk*) ; 
 int /*<<< orphan*/  disk_ll_save_ie ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int sm_ll_init (struct ll_disk*,struct dm_transaction_manager*) ; 
 int stub1 (struct ll_disk*) ; 

int sm_ll_open_disk(struct ll_disk *ll, struct dm_transaction_manager *tm,
		    void *root_le, size_t len)
{
	int r;
	struct disk_sm_root *smr = root_le;

	if (len < sizeof(struct disk_sm_root)) {
		DMERR("sm_metadata root too small");
		return -ENOMEM;
	}

	r = sm_ll_init(ll, tm);
	if (r < 0)
		return r;

	ll->load_ie = disk_ll_load_ie;
	ll->save_ie = disk_ll_save_ie;
	ll->init_index = disk_ll_init_index;
	ll->open_index = disk_ll_open;
	ll->max_entries = disk_ll_max_entries;
	ll->commit = disk_ll_commit;

	ll->nr_blocks = le64_to_cpu(smr->nr_blocks);
	ll->nr_allocated = le64_to_cpu(smr->nr_allocated);
	ll->bitmap_root = le64_to_cpu(smr->bitmap_root);
	ll->ref_count_root = le64_to_cpu(smr->ref_count_root);

	return ll->open_index(ll);
}