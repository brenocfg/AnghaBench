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
struct oxu_info {int /*<<< orphan*/ * hcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  oxu_remove (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct oxu_info* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int oxu_drv_remove(struct platform_device *pdev)
{
	struct oxu_info *info = platform_get_drvdata(pdev);

	oxu_remove(pdev, info->hcd[0]);
	oxu_remove(pdev, info->hcd[1]);

	return 0;
}