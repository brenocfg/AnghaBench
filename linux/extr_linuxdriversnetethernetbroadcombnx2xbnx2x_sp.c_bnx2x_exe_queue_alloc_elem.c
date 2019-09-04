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
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct bnx2x_exeq_elem* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct bnx2x_exeq_elem *bnx2x_exe_queue_alloc_elem(
	struct bnx2x *bp)
{
	DP(BNX2X_MSG_SP, "Allocating a new exe_queue element\n");
	return kzalloc(sizeof(struct bnx2x_exeq_elem), GFP_ATOMIC);
}