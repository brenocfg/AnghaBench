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
struct bnx2x_exeq_elem {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct bnx2x_exeq_elem*) ; 

__attribute__((used)) static inline void bnx2x_exe_queue_free_elem(struct bnx2x *bp,
					     struct bnx2x_exeq_elem *elem)
{
	DP(BNX2X_MSG_SP, "Deleting an exe_queue element\n");
	kfree(elem);
}