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
struct au0828_rc {int /*<<< orphan*/  rc; } ;
struct au0828_dev {struct au0828_rc* ir; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct au0828_rc*) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 

void au0828_rc_unregister(struct au0828_dev *dev)
{
	struct au0828_rc *ir = dev->ir;

	/* skip detach on non attached boards */
	if (!ir)
		return;

	rc_unregister_device(ir->rc);

	/* done */
	kfree(ir);
	dev->ir = NULL;
}