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
struct tegra_dc {unsigned int pipe; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tegra_dc* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int tegra_dc_match_by_pipe(struct device *dev, const void *data)
{
	struct tegra_dc *dc = dev_get_drvdata(dev);
	unsigned int pipe = (unsigned long)(void *)data;

	return dc->pipe == pipe;
}