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
struct omap_dss_device {int /*<<< orphan*/  dev; } ;
struct dsi_data {int dummy; } ;

/* Variables and functions */
 struct dsi_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct dsi_data *to_dsi_data(struct omap_dss_device *dssdev)
{
	return dev_get_drvdata(dssdev->dev);
}