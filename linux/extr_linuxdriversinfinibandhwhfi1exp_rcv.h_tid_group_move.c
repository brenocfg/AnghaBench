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
struct tid_group {int dummy; } ;
struct exp_tid_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tid_group_add_tail (struct tid_group*,struct exp_tid_set*) ; 
 int /*<<< orphan*/  tid_group_remove (struct tid_group*,struct exp_tid_set*) ; 

__attribute__((used)) static inline void tid_group_move(struct tid_group *group,
				  struct exp_tid_set *s1,
				  struct exp_tid_set *s2)
{
	tid_group_remove(group, s1);
	tid_group_add_tail(group, s2);
}