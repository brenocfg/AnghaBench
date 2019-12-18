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
struct hibmc_drm_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hibmc_hw_config (struct hibmc_drm_private*) ; 
 int hibmc_hw_map (struct hibmc_drm_private*) ; 

__attribute__((used)) static int hibmc_hw_init(struct hibmc_drm_private *priv)
{
	int ret;

	ret = hibmc_hw_map(priv);
	if (ret)
		return ret;

	hibmc_hw_config(priv);

	return 0;
}