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
struct au0828_rc {int /*<<< orphan*/  work; } ;
struct au0828_dev {struct au0828_rc* ir; } ;

/* Variables and functions */
 int /*<<< orphan*/  au8522_rc_clear (struct au0828_rc*,int,int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

int au0828_rc_suspend(struct au0828_dev *dev)
{
	struct au0828_rc *ir = dev->ir;

	if (!ir)
		return 0;

	pr_info("Stopping RC\n");

	cancel_delayed_work_sync(&ir->work);

	/* Disable IR */
	au8522_rc_clear(ir, 0xe0, 1 << 4);

	return 0;
}