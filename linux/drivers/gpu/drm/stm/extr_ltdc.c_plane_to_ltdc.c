#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ltdc_device {int dummy; } ;
struct drm_plane {TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ dev_private; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ltdc_device *plane_to_ltdc(struct drm_plane *plane)
{
	return (struct ltdc_device *)plane->dev->dev_private;
}