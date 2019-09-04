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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  component_drivers ; 
 int component_master_add_with_match (struct device*,int /*<<< orphan*/ *,struct component_match*) ; 
 int /*<<< orphan*/  vc4_drm_ops ; 
 int /*<<< orphan*/  vc4_match_add_drivers (struct device*,struct component_match**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc4_platform_drm_probe(struct platform_device *pdev)
{
	struct component_match *match = NULL;
	struct device *dev = &pdev->dev;

	vc4_match_add_drivers(dev, &match,
			      component_drivers, ARRAY_SIZE(component_drivers));

	return component_master_add_with_match(dev, &vc4_drm_ops, match);
}