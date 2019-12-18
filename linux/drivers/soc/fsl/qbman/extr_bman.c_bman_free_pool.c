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
struct bman_pool {int /*<<< orphan*/  bpid; } ;

/* Variables and functions */
 int /*<<< orphan*/  bm_release_bpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bman_pool*) ; 

void bman_free_pool(struct bman_pool *pool)
{
	bm_release_bpid(pool->bpid);

	kfree(pool);
}