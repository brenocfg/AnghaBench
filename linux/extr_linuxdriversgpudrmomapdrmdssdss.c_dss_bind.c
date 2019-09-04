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
struct dss_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int component_bind_all (struct device*,int /*<<< orphan*/ *) ; 
 struct dss_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  omapdss_gather_components (struct device*) ; 
 int /*<<< orphan*/  omapdss_set_dss (struct dss_device*) ; 
 int /*<<< orphan*/  pm_set_vt_switch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dss_bind(struct device *dev)
{
	struct dss_device *dss = dev_get_drvdata(dev);
	int r;

	r = component_bind_all(dev, NULL);
	if (r)
		return r;

	pm_set_vt_switch(0);

	omapdss_gather_components(dev);
	omapdss_set_dss(dss);

	return 0;
}