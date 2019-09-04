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
struct nes_cm_node {int accelerated; TYPE_1__* listener; scalar_t__ accept_pend; } ;
struct nes_cm_core {int /*<<< orphan*/  tcp_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  pend_accepts_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ NES_SHORT_TIME ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int mini_cm_accelerated(struct nes_cm_core *cm_core,
				      struct nes_cm_node *cm_node)
{
	cm_node->accelerated = true;

	if (cm_node->accept_pend) {
		BUG_ON(!cm_node->listener);
		atomic_dec(&cm_node->listener->pend_accepts_cnt);
		cm_node->accept_pend = 0;
		BUG_ON(atomic_read(&cm_node->listener->pend_accepts_cnt) < 0);
	}

	if (!timer_pending(&cm_core->tcp_timer))
		mod_timer(&cm_core->tcp_timer, (jiffies + NES_SHORT_TIME));

	return 0;
}