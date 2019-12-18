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
struct sm_metadata {int /*<<< orphan*/  uncommitted; } ;
typedef  enum block_op_type { ____Placeholder_block_op_type } block_op_type ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int ENOMEM ; 
 int brb_push (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_bop(struct sm_metadata *smm, enum block_op_type type, dm_block_t b)
{
	int r = brb_push(&smm->uncommitted, type, b);

	if (r) {
		DMERR("too many recursive allocations");
		return -ENOMEM;
	}

	return 0;
}