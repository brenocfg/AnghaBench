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
struct wm97xx {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct wm97xx* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  wm97xx_unregister_mach_ops (struct wm97xx*) ; 

__attribute__((used)) static int zylonite_wm97xx_remove(struct platform_device *pdev)
{
	struct wm97xx *wm = platform_get_drvdata(pdev);

	wm97xx_unregister_mach_ops(wm);

	return 0;
}