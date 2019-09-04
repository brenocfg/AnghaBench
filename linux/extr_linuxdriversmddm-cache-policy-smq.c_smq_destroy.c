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
struct smq_policy {int /*<<< orphan*/  es; int /*<<< orphan*/  cache_hit_bits; int /*<<< orphan*/  hotspot_hit_bits; int /*<<< orphan*/  table; int /*<<< orphan*/  hotspot_table; int /*<<< orphan*/  bg_work; } ;
struct dm_cache_policy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btracker_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_bitset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct smq_policy*) ; 
 int /*<<< orphan*/  space_exit (int /*<<< orphan*/ *) ; 
 struct smq_policy* to_smq_policy (struct dm_cache_policy*) ; 

__attribute__((used)) static void smq_destroy(struct dm_cache_policy *p)
{
	struct smq_policy *mq = to_smq_policy(p);

	btracker_destroy(mq->bg_work);
	h_exit(&mq->hotspot_table);
	h_exit(&mq->table);
	free_bitset(mq->hotspot_hit_bits);
	free_bitset(mq->cache_hit_bits);
	space_exit(&mq->es);
	kfree(mq);
}