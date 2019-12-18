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
typedef  int /*<<< orphan*/  u32 ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ drm_max_vblank_count (struct drm_device*,unsigned int) ; 

__attribute__((used)) static u32 drm_vblank_no_hw_counter(struct drm_device *dev, unsigned int pipe)
{
	WARN_ON_ONCE(drm_max_vblank_count(dev, pipe) != 0);
	return 0;
}