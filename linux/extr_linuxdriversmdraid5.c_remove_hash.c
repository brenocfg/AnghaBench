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
struct stripe_head {int /*<<< orphan*/  hash; scalar_t__ sector; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long) ; 

__attribute__((used)) static inline void remove_hash(struct stripe_head *sh)
{
	pr_debug("remove_hash(), stripe %llu\n",
		(unsigned long long)sh->sector);

	hlist_del_init(&sh->hash);
}