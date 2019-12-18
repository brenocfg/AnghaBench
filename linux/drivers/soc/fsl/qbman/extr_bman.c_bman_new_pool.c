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
struct bman_pool {int /*<<< orphan*/  bpid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ bm_alloc_bpid_range (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bm_release_bpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bman_pool*) ; 
 struct bman_pool* kmalloc (int,int /*<<< orphan*/ ) ; 

struct bman_pool *bman_new_pool(void)
{
	struct bman_pool *pool = NULL;
	u32 bpid;

	if (bm_alloc_bpid_range(&bpid, 1))
		return NULL;

	pool = kmalloc(sizeof(*pool), GFP_KERNEL);
	if (!pool)
		goto err;

	pool->bpid = bpid;

	return pool;
err:
	bm_release_bpid(bpid);
	kfree(pool);
	return NULL;
}