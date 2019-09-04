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
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int mdp5_init (struct platform_device*,struct drm_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int mdp5_bind(struct device *dev, struct device *master, void *data)
{
	struct drm_device *ddev = dev_get_drvdata(master);
	struct platform_device *pdev = to_platform_device(dev);

	DBG("");

	return mdp5_init(pdev, ddev);
}