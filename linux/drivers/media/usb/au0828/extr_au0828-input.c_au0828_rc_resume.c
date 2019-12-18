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
struct au0828_rc {int /*<<< orphan*/  polling; int /*<<< orphan*/  work; } ;
struct au0828_dev {struct au0828_rc* ir; } ;

/* Variables and functions */
 int /*<<< orphan*/  au8522_rc_set (struct au0828_rc*,int,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int au0828_rc_resume(struct au0828_dev *dev)
{
	struct au0828_rc *ir = dev->ir;

	if (!ir)
		return 0;

	pr_info("Restarting RC\n");

	/* Enable IR */
	au8522_rc_set(ir, 0xe0, 1 << 4);

	schedule_delayed_work(&ir->work, msecs_to_jiffies(ir->polling));

	return 0;
}