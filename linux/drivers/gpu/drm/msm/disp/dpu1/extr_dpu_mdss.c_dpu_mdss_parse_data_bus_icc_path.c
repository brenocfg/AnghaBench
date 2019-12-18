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
struct icc_path {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct dpu_mdss {int num_paths; struct icc_path** path; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct icc_path*) ; 
 int PTR_ERR_OR_ZERO (struct icc_path*) ; 
 struct icc_path* of_icc_get (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dpu_mdss_parse_data_bus_icc_path(struct drm_device *dev,
						struct dpu_mdss *dpu_mdss)
{
	struct icc_path *path0 = of_icc_get(dev->dev, "mdp0-mem");
	struct icc_path *path1 = of_icc_get(dev->dev, "mdp1-mem");

	if (IS_ERR_OR_NULL(path0))
		return PTR_ERR_OR_ZERO(path0);

	dpu_mdss->path[0] = path0;
	dpu_mdss->num_paths = 1;

	if (!IS_ERR_OR_NULL(path1)) {
		dpu_mdss->path[1] = path1;
		dpu_mdss->num_paths++;
	}

	return 0;
}