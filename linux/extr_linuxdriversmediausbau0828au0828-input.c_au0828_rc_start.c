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
struct rc_dev {struct au0828_rc* priv; } ;
struct au0828_rc {int /*<<< orphan*/  polling; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au0828_rc_work ; 
 int /*<<< orphan*/  au8522_rc_set (struct au0828_rc*,int,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au0828_rc_start(struct rc_dev *rc)
{
	struct au0828_rc *ir = rc->priv;

	INIT_DELAYED_WORK(&ir->work, au0828_rc_work);

	/* Enable IR */
	au8522_rc_set(ir, 0xe0, 1 << 4);

	schedule_delayed_work(&ir->work, msecs_to_jiffies(ir->polling));

	return 0;
}