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

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 

__attribute__((used)) static int sti_gdp_get_dst(struct device *dev, int dst, int src)
{
	if (dst == src)
		return dst;

	if (dst < src) {
		dev_dbg(dev, "WARNING: GDP scale not supported, will crop\n");
		return dst;
	}

	dev_dbg(dev, "WARNING: GDP scale not supported, will clamp\n");
	return src;
}