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
struct dm_transaction_manager {int dummy; } ;
typedef  struct dm_transaction_manager dm_space_map ;
struct dm_block_manager {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 scalar_t__ IS_ERR (struct dm_transaction_manager*) ; 
 int PTR_ERR (struct dm_transaction_manager*) ; 
 int /*<<< orphan*/  dm_bm_nr_blocks (struct dm_block_manager*) ; 
 int /*<<< orphan*/  dm_sm_destroy (struct dm_transaction_manager*) ; 
 int dm_sm_metadata_create (struct dm_transaction_manager*,struct dm_transaction_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dm_transaction_manager* dm_sm_metadata_init () ; 
 int dm_sm_metadata_open (struct dm_transaction_manager*,struct dm_transaction_manager*,void*,size_t) ; 
 struct dm_transaction_manager* dm_tm_create (struct dm_block_manager*,struct dm_transaction_manager*) ; 
 int /*<<< orphan*/  dm_tm_destroy (struct dm_transaction_manager*) ; 

__attribute__((used)) static int dm_tm_create_internal(struct dm_block_manager *bm,
				 dm_block_t sb_location,
				 struct dm_transaction_manager **tm,
				 struct dm_space_map **sm,
				 int create,
				 void *sm_root, size_t sm_len)
{
	int r;

	*sm = dm_sm_metadata_init();
	if (IS_ERR(*sm))
		return PTR_ERR(*sm);

	*tm = dm_tm_create(bm, *sm);
	if (IS_ERR(*tm)) {
		dm_sm_destroy(*sm);
		return PTR_ERR(*tm);
	}

	if (create) {
		r = dm_sm_metadata_create(*sm, *tm, dm_bm_nr_blocks(bm),
					  sb_location);
		if (r) {
			DMERR("couldn't create metadata space map");
			goto bad;
		}

	} else {
		r = dm_sm_metadata_open(*sm, *tm, sm_root, sm_len);
		if (r) {
			DMERR("couldn't open metadata space map");
			goto bad;
		}
	}

	return 0;

bad:
	dm_tm_destroy(*tm);
	dm_sm_destroy(*sm);
	return r;
}