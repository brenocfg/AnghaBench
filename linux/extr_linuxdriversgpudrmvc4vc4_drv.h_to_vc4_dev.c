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
struct vc4_dev {int dummy; } ;
struct drm_device {scalar_t__ dev_private; } ;

/* Variables and functions */

__attribute__((used)) static inline struct vc4_dev *
to_vc4_dev(struct drm_device *dev)
{
	return (struct vc4_dev *)dev->dev_private;
}