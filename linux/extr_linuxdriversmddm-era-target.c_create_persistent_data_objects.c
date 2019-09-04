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
struct era_metadata {int /*<<< orphan*/  bm; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  DM_ERA_METADATA_BLOCK_SIZE ; 
 int /*<<< orphan*/  ERA_MAX_CONCURRENT_LOCKS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_block_manager_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_block_manager_destroy (int /*<<< orphan*/ ) ; 
 int open_or_format_metadata (struct era_metadata*,int) ; 

__attribute__((used)) static int create_persistent_data_objects(struct era_metadata *md,
					  bool may_format)
{
	int r;

	md->bm = dm_block_manager_create(md->bdev, DM_ERA_METADATA_BLOCK_SIZE,
					 ERA_MAX_CONCURRENT_LOCKS);
	if (IS_ERR(md->bm)) {
		DMERR("could not create block manager");
		return PTR_ERR(md->bm);
	}

	r = open_or_format_metadata(md, may_format);
	if (r)
		dm_block_manager_destroy(md->bm);

	return r;
}