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
struct host1x {int /*<<< orphan*/  group; scalar_t__ domain; int /*<<< orphan*/  iova; int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_intr_deinit (struct host1x*) ; 
 int /*<<< orphan*/  host1x_syncpt_deinit (struct host1x*) ; 
 int /*<<< orphan*/  host1x_unregister (struct host1x*) ; 
 int /*<<< orphan*/  iommu_detach_group (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_domain_free (scalar_t__) ; 
 int /*<<< orphan*/  iommu_group_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iova_cache_put () ; 
 struct host1x* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  put_iova_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int host1x_remove(struct platform_device *pdev)
{
	struct host1x *host = platform_get_drvdata(pdev);

	host1x_unregister(host);
	host1x_intr_deinit(host);
	host1x_syncpt_deinit(host);
	reset_control_assert(host->rst);
	clk_disable_unprepare(host->clk);

	if (host->domain) {
		put_iova_domain(&host->iova);
		iommu_detach_group(host->domain, host->group);
		iommu_domain_free(host->domain);
		iova_cache_put();
		iommu_group_put(host->group);
	}

	return 0;
}