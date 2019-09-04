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
struct videomode {int dummy; } ;
struct omap_dss_device {int dummy; } ;
struct dpi_data {int /*<<< orphan*/  lock; struct videomode vm; } ;

/* Variables and functions */
 struct dpi_data* dpi_get_data_from_dssdev (struct omap_dss_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dpi_get_timings(struct omap_dss_device *dssdev,
			    struct videomode *vm)
{
	struct dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);

	mutex_lock(&dpi->lock);

	*vm = dpi->vm;

	mutex_unlock(&dpi->lock);
}