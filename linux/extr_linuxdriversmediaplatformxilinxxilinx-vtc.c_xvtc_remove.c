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
struct xvtc_device {int /*<<< orphan*/  xvip; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct xvtc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  xvip_cleanup_resources (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xvtc_unregister_device (struct xvtc_device*) ; 

__attribute__((used)) static int xvtc_remove(struct platform_device *pdev)
{
	struct xvtc_device *xvtc = platform_get_drvdata(pdev);

	xvtc_unregister_device(xvtc);

	xvip_cleanup_resources(&xvtc->xvip);

	return 0;
}