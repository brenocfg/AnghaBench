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
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  drm_mga_dma_bootstrap_t ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int mga_do_agp_dma_bootstrap(struct drm_device *dev,
				    drm_mga_dma_bootstrap_t *dma_bs)
{
	return -EINVAL;
}