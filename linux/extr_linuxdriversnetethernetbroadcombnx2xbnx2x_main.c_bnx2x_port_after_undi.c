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
struct bnx2x_prev_path_list {int undi; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BP_PORT (struct bnx2x*) ; 
 struct bnx2x_prev_path_list* bnx2x_prev_path_get_entry (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_prev_sem ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

bool bnx2x_port_after_undi(struct bnx2x *bp)
{
	struct bnx2x_prev_path_list *entry;
	bool val;

	down(&bnx2x_prev_sem);

	entry = bnx2x_prev_path_get_entry(bp);
	val = !!(entry && (entry->undi & (1 << BP_PORT(bp))));

	up(&bnx2x_prev_sem);

	return val;
}