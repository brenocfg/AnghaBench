#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct bas_bc_state* bas; } ;
struct bc_state {TYPE_1__ hw; } ;
struct bas_bc_state {int /*<<< orphan*/  loststatus; int /*<<< orphan*/  isoinlock; int /*<<< orphan*/  isooutlock; scalar_t__ numsub; int /*<<< orphan*/  corrbytes; scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gigaset_reinitbcshw(struct bc_state *bcs)
{
	struct bas_bc_state *ubc = bcs->hw.bas;

	bcs->hw.bas->running = 0;
	atomic_set(&bcs->hw.bas->corrbytes, 0);
	bcs->hw.bas->numsub = 0;
	spin_lock_init(&ubc->isooutlock);
	spin_lock_init(&ubc->isoinlock);
	ubc->loststatus = -EINPROGRESS;
}