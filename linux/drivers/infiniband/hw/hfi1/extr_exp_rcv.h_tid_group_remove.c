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
struct tid_group {int /*<<< orphan*/  list; } ;
struct exp_tid_set {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void tid_group_remove(struct tid_group *grp,
				    struct exp_tid_set *set)
{
	list_del_init(&grp->list);
	set->count--;
}