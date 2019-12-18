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

/* Variables and functions */
 int /*<<< orphan*/  dpaa2_aiop_console_dev ; 
 int /*<<< orphan*/  dpaa2_mc_console_dev ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dpaa2_console_remove(struct platform_device *pdev)
{
	misc_deregister(&dpaa2_mc_console_dev);
	misc_deregister(&dpaa2_aiop_console_dev);

	return 0;
}