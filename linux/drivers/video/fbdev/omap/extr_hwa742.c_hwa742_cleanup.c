#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sys_ck; TYPE_2__* int_ctrl; TYPE_1__* extif; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cleanup ) () ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* cleanup ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  OMAPFB_UPDATE_DISABLED ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 TYPE_3__ hwa742 ; 
 int /*<<< orphan*/  hwa742_set_update_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static void hwa742_cleanup(void)
{
	hwa742_set_update_mode(OMAPFB_UPDATE_DISABLED);
	hwa742.extif->cleanup();
	hwa742.int_ctrl->cleanup();
	clk_disable(hwa742.sys_ck);
}