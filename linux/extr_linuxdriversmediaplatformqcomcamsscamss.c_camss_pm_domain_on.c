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
struct camss {scalar_t__ version; int /*<<< orphan*/ * genpd_link; int /*<<< orphan*/ * genpd; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CAMSS_8x96 ; 
 int DL_FLAG_PM_RUNTIME ; 
 int DL_FLAG_RPM_ACTIVE ; 
 int DL_FLAG_STATELESS ; 
 int EINVAL ; 
 int /*<<< orphan*/  device_link_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int camss_pm_domain_on(struct camss *camss, int id)
{
	if (camss->version == CAMSS_8x96) {
		camss->genpd_link[id] = device_link_add(camss->dev,
				camss->genpd[id], DL_FLAG_STATELESS |
				DL_FLAG_PM_RUNTIME | DL_FLAG_RPM_ACTIVE);

		if (!camss->genpd_link[id])
			return -EINVAL;
	}

	return 0;
}