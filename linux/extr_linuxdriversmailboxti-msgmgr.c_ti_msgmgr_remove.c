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
struct ti_msgmgr_inst {int /*<<< orphan*/  mbox; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_controller_unregister (int /*<<< orphan*/ *) ; 
 struct ti_msgmgr_inst* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ti_msgmgr_remove(struct platform_device *pdev)
{
	struct ti_msgmgr_inst *inst;

	inst = platform_get_drvdata(pdev);
	mbox_controller_unregister(&inst->mbox);

	return 0;
}