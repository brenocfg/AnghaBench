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

/* Variables and functions */
 int /*<<< orphan*/  FULL_CLEANUP ; 
 int /*<<< orphan*/  mga_do_cleanup_dma (struct drm_device*,int /*<<< orphan*/ ) ; 

void mga_driver_lastclose(struct drm_device *dev)
{
	mga_do_cleanup_dma(dev, FULL_CLEANUP);
}