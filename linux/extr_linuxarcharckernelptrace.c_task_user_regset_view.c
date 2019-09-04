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
struct user_regset_view {int dummy; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 struct user_regset_view const user_arc_view ; 

const struct user_regset_view *task_user_regset_view(struct task_struct *task)
{
	return &user_arc_view;
}