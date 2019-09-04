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
struct platform_device {int dummy; } ;
struct hi6220_mbox {int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_controller_unregister (int /*<<< orphan*/ *) ; 
 struct hi6220_mbox* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int hi6220_mbox_remove(struct platform_device *pdev)
{
	struct hi6220_mbox *mbox = platform_get_drvdata(pdev);

	mbox_controller_unregister(&mbox->controller);
	return 0;
}