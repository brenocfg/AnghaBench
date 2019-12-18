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
struct era_metadata {int /*<<< orphan*/  tm; int /*<<< orphan*/  sm; int /*<<< orphan*/  era_array_root; int /*<<< orphan*/  era_array_info; int /*<<< orphan*/  writeset_tree_root; int /*<<< orphan*/  writeset_tree_info; int /*<<< orphan*/  bm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  SUPERBLOCK_LOCATION ; 
 int dm_array_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dm_btree_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_sm_destroy (int /*<<< orphan*/ ) ; 
 int dm_tm_create_with_sm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_tm_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_infos (struct era_metadata*) ; 

__attribute__((used)) static int create_fresh_metadata(struct era_metadata *md)
{
	int r;

	r = dm_tm_create_with_sm(md->bm, SUPERBLOCK_LOCATION,
				 &md->tm, &md->sm);
	if (r < 0) {
		DMERR("dm_tm_create_with_sm failed");
		return r;
	}

	setup_infos(md);

	r = dm_btree_empty(&md->writeset_tree_info, &md->writeset_tree_root);
	if (r) {
		DMERR("couldn't create new writeset tree");
		goto bad;
	}

	r = dm_array_empty(&md->era_array_info, &md->era_array_root);
	if (r) {
		DMERR("couldn't create era array");
		goto bad;
	}

	return 0;

bad:
	dm_sm_destroy(md->sm);
	dm_tm_destroy(md->tm);

	return r;
}