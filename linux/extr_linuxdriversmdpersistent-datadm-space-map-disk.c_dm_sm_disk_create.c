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
struct dm_space_map {int dummy; } ;
struct sm_disk {struct dm_space_map sm; int /*<<< orphan*/  ll; scalar_t__ nr_allocated_this_transaction; scalar_t__ begin; } ;
struct dm_transaction_manager {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct dm_space_map* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct sm_disk*) ; 
 struct sm_disk* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct dm_space_map*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ops ; 
 int sm_disk_commit (struct dm_space_map*) ; 
 int sm_ll_extend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sm_ll_new_disk (int /*<<< orphan*/ *,struct dm_transaction_manager*) ; 

struct dm_space_map *dm_sm_disk_create(struct dm_transaction_manager *tm,
				       dm_block_t nr_blocks)
{
	int r;
	struct sm_disk *smd;

	smd = kmalloc(sizeof(*smd), GFP_KERNEL);
	if (!smd)
		return ERR_PTR(-ENOMEM);

	smd->begin = 0;
	smd->nr_allocated_this_transaction = 0;
	memcpy(&smd->sm, &ops, sizeof(smd->sm));

	r = sm_ll_new_disk(&smd->ll, tm);
	if (r)
		goto bad;

	r = sm_ll_extend(&smd->ll, nr_blocks);
	if (r)
		goto bad;

	r = sm_disk_commit(&smd->sm);
	if (r)
		goto bad;

	return &smd->sm;

bad:
	kfree(smd);
	return ERR_PTR(r);
}