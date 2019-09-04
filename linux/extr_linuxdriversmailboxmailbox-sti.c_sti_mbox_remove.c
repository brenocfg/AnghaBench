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
struct sti_mbox_device {int /*<<< orphan*/  mbox; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_controller_unregister (int /*<<< orphan*/ ) ; 
 struct sti_mbox_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int sti_mbox_remove(struct platform_device *pdev)
{
	struct sti_mbox_device *mdev = platform_get_drvdata(pdev);

	mbox_controller_unregister(mdev->mbox);

	return 0;
}