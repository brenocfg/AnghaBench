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
struct isp_device {int /*<<< orphan*/  notifier; int /*<<< orphan*/  crashed; } ;

/* Variables and functions */
 int /*<<< orphan*/  __omap3isp_get (struct isp_device*,int) ; 
 int /*<<< orphan*/  __omap3isp_put (struct isp_device*,int) ; 
 int /*<<< orphan*/  isp_cleanup_modules (struct isp_device*) ; 
 int /*<<< orphan*/  isp_detach_iommu (struct isp_device*) ; 
 int /*<<< orphan*/  isp_unregister_entities (struct isp_device*) ; 
 int /*<<< orphan*/  isp_xclk_cleanup (struct isp_device*) ; 
 int /*<<< orphan*/  kfree (struct isp_device*) ; 
 int /*<<< orphan*/  media_entity_enum_cleanup (int /*<<< orphan*/ *) ; 
 struct isp_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isp_remove(struct platform_device *pdev)
{
	struct isp_device *isp = platform_get_drvdata(pdev);

	v4l2_async_notifier_unregister(&isp->notifier);
	isp_unregister_entities(isp);
	isp_cleanup_modules(isp);
	isp_xclk_cleanup(isp);

	__omap3isp_get(isp, false);
	isp_detach_iommu(isp);
	__omap3isp_put(isp, false);

	media_entity_enum_cleanup(&isp->crashed);
	v4l2_async_notifier_cleanup(&isp->notifier);

	kfree(isp);

	return 0;
}