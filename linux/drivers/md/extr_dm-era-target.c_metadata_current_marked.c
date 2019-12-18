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
struct writeset {int dummy; } ;
struct era_metadata {int /*<<< orphan*/  current_writeset; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 struct writeset* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int writeset_marked (struct writeset*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool metadata_current_marked(struct era_metadata *md, dm_block_t block)
{
	bool r;
	struct writeset *ws;

	rcu_read_lock();
	ws = rcu_dereference(md->current_writeset);
	r = writeset_marked(ws, block);
	rcu_read_unlock();

	return r;
}