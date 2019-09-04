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
 TYPE_2__* local_paca ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool kvmppc_tb_resync_required(void)
{
	if (test_and_set_bit(CORE_TB_RESYNC_REQ_BIT,
				&local_paca->sibling_subcore_state->flags))
		return false;

	return true;
}