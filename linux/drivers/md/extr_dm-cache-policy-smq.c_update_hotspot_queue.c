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
struct smq_policy {unsigned int hotspot_level_jump; int /*<<< orphan*/  hotspot_table; int /*<<< orphan*/  hotspot; int /*<<< orphan*/  hotspot_hit_bits; int /*<<< orphan*/  hotspot_alloc; int /*<<< orphan*/  hotspot_stats; } ;
struct entry {int /*<<< orphan*/  oblock; int /*<<< orphan*/  level; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;

/* Variables and functions */
 struct entry* alloc_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int get_index (int /*<<< orphan*/ *,struct entry*) ; 
 int /*<<< orphan*/  h_insert (int /*<<< orphan*/ *,struct entry*) ; 
 struct entry* h_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h_remove (int /*<<< orphan*/ *,struct entry*) ; 
 struct entry* q_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  q_push (int /*<<< orphan*/ *,struct entry*) ; 
 int /*<<< orphan*/  q_requeue (int /*<<< orphan*/ *,struct entry*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stats_level_accessed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_miss (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_hblock (struct smq_policy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct entry *update_hotspot_queue(struct smq_policy *mq, dm_oblock_t b)
{
	unsigned hi;
	dm_oblock_t hb = to_hblock(mq, b);
	struct entry *e = h_lookup(&mq->hotspot_table, hb);

	if (e) {
		stats_level_accessed(&mq->hotspot_stats, e->level);

		hi = get_index(&mq->hotspot_alloc, e);
		q_requeue(&mq->hotspot, e,
			  test_and_set_bit(hi, mq->hotspot_hit_bits) ?
			  0u : mq->hotspot_level_jump,
			  NULL, NULL);

	} else {
		stats_miss(&mq->hotspot_stats);

		e = alloc_entry(&mq->hotspot_alloc);
		if (!e) {
			e = q_pop(&mq->hotspot);
			if (e) {
				h_remove(&mq->hotspot_table, e);
				hi = get_index(&mq->hotspot_alloc, e);
				clear_bit(hi, mq->hotspot_hit_bits);
			}

		}

		if (e) {
			e->oblock = hb;
			q_push(&mq->hotspot, e);
			h_insert(&mq->hotspot_table, e);
		}
	}

	return e;
}