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
struct panfrost_device {int dummy; } ;
struct drm_device {struct panfrost_device* dev_private; } ;

/* Variables and functions */

__attribute__((used)) static inline struct panfrost_device *to_panfrost_device(struct drm_device *ddev)
{
	return ddev->dev_private;
}