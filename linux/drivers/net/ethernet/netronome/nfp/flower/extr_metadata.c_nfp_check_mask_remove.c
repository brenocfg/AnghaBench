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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nfp_mask_id_table {int /*<<< orphan*/  link; int /*<<< orphan*/  ref_cnt; int /*<<< orphan*/  mask_id; } ;
struct nfp_app {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_FL_META_FLAG_MANAGE_MASK ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nfp_mask_id_table*) ; 
 int /*<<< orphan*/  nfp_release_mask_id (struct nfp_app*,int /*<<< orphan*/ ) ; 
 struct nfp_mask_id_table* nfp_search_mask_table (struct nfp_app*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nfp_check_mask_remove(struct nfp_app *app, char *mask_data, u32 mask_len,
		      u8 *meta_flags, u8 *mask_id)
{
	struct nfp_mask_id_table *mask_entry;

	mask_entry = nfp_search_mask_table(app, mask_data, mask_len);
	if (!mask_entry)
		return false;

	*mask_id = mask_entry->mask_id;
	mask_entry->ref_cnt--;
	if (!mask_entry->ref_cnt) {
		hash_del(&mask_entry->link);
		nfp_release_mask_id(app, *mask_id);
		kfree(mask_entry);
		if (meta_flags)
			*meta_flags |= NFP_FL_META_FLAG_MANAGE_MASK;
	}

	return true;
}