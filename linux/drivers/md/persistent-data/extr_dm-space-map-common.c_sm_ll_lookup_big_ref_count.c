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
typedef  int /*<<< orphan*/  uint32_t ;
struct ll_disk {int /*<<< orphan*/  ref_count_root; int /*<<< orphan*/  ref_count_info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int dm_btree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sm_ll_lookup_big_ref_count(struct ll_disk *ll, dm_block_t b,
				      uint32_t *result)
{
	__le32 le_rc;
	int r;

	r = dm_btree_lookup(&ll->ref_count_info, ll->ref_count_root, &b, &le_rc);
	if (r < 0)
		return r;

	*result = le32_to_cpu(le_rc);

	return r;
}