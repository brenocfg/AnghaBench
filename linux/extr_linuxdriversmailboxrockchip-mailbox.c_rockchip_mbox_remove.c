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
struct rockchip_mbox {int /*<<< orphan*/  mbox; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mbox_controller_unregister (int /*<<< orphan*/ *) ; 
 struct rockchip_mbox* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int rockchip_mbox_remove(struct platform_device *pdev)
{
	struct rockchip_mbox *mb = platform_get_drvdata(pdev);

	if (!mb)
		return -EINVAL;

	mbox_controller_unregister(&mb->mbox);

	return 0;
}