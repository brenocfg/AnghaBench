#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct syscon {struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct regmap* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct syscon* dev_get_drvdata (struct device*) ; 
 struct device* driver_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 TYPE_1__ syscon_driver ; 
 int /*<<< orphan*/  syscon_match_pdevname ; 

struct regmap *syscon_regmap_lookup_by_pdevname(const char *s)
{
	struct device *dev;
	struct syscon *syscon;

	dev = driver_find_device(&syscon_driver.driver, NULL, (void *)s,
				 syscon_match_pdevname);
	if (!dev)
		return ERR_PTR(-EPROBE_DEFER);

	syscon = dev_get_drvdata(dev);

	return syscon->regmap;
}