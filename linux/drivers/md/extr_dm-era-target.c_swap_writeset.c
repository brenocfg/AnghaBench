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

/* Variables and functions */
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct writeset*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void swap_writeset(struct era_metadata *md, struct writeset *new_writeset)
{
	rcu_assign_pointer(md->current_writeset, new_writeset);
	synchronize_rcu();
}