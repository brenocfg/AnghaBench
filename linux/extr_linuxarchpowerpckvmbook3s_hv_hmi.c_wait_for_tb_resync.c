#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* sibling_subcore_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_TB_RESYNC_REQ_BIT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_2__* local_paca ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void wait_for_tb_resync(void)
{
	if (!local_paca->sibling_subcore_state)
		return;

	while (test_bit(CORE_TB_RESYNC_REQ_BIT,
				&local_paca->sibling_subcore_state->flags))
		cpu_relax();
}