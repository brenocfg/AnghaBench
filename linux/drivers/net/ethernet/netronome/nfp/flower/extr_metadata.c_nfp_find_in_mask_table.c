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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_mask_id_table {int mask_id; int /*<<< orphan*/  ref_cnt; } ;
struct nfp_app {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct nfp_mask_id_table* nfp_search_mask_table (struct nfp_app*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_find_in_mask_table(struct nfp_app *app, char *mask_data, u32 mask_len)
{
	struct nfp_mask_id_table *mask_entry;

	mask_entry = nfp_search_mask_table(app, mask_data, mask_len);
	if (!mask_entry)
		return -ENOENT;

	mask_entry->ref_cnt++;

	/* Casting u8 to int for later use. */
	return mask_entry->mask_id;
}