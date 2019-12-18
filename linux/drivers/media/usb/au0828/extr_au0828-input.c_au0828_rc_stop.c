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
struct rc_dev {struct au0828_rc* priv; } ;
struct au0828_rc {TYPE_1__* dev; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_DISCONNECTED ; 
 int /*<<< orphan*/  au8522_rc_clear (struct au0828_rc*,int,int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void au0828_rc_stop(struct rc_dev *rc)
{
	struct au0828_rc *ir = rc->priv;

	cancel_delayed_work_sync(&ir->work);

	/* do nothing if device is disconnected */
	if (!test_bit(DEV_DISCONNECTED, &ir->dev->dev_state)) {
		/* Disable IR */
		au8522_rc_clear(ir, 0xe0, 1 << 4);
	}
}