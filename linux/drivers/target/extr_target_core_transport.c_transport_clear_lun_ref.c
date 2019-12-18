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
struct se_lun {int /*<<< orphan*/  lun_shutdown_comp; int /*<<< orphan*/  lun_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  percpu_ref_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void transport_clear_lun_ref(struct se_lun *lun)
{
	percpu_ref_kill(&lun->lun_ref);
	wait_for_completion(&lun->lun_shutdown_comp);
}