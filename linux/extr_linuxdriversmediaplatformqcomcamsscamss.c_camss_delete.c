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
struct camss {scalar_t__ version; int /*<<< orphan*/ * genpd; int /*<<< orphan*/  dev; int /*<<< orphan*/  media_dev; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 scalar_t__ CAMSS_8x96 ; 
 size_t PM_DOMAIN_VFE0 ; 
 size_t PM_DOMAIN_VFE1 ; 
 int /*<<< orphan*/  dev_pm_domain_detach (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct camss*) ; 
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

void camss_delete(struct camss *camss)
{
	v4l2_device_unregister(&camss->v4l2_dev);
	media_device_unregister(&camss->media_dev);
	media_device_cleanup(&camss->media_dev);

	pm_runtime_disable(camss->dev);

	if (camss->version == CAMSS_8x96) {
		dev_pm_domain_detach(camss->genpd[PM_DOMAIN_VFE0], true);
		dev_pm_domain_detach(camss->genpd[PM_DOMAIN_VFE1], true);
	}

	kfree(camss);
}