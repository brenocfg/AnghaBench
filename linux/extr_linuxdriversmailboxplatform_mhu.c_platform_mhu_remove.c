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
struct platform_mhu {int /*<<< orphan*/  mbox; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_controller_unregister (int /*<<< orphan*/ *) ; 
 struct platform_mhu* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int platform_mhu_remove(struct platform_device *pdev)
{
	struct platform_mhu *mhu = platform_get_drvdata(pdev);

	mbox_controller_unregister(&mhu->mbox);

	return 0;
}