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
struct lima_device {int dummy; } ;
struct drm_device {struct lima_device* dev_private; } ;

/* Variables and functions */

__attribute__((used)) static inline struct lima_device *
to_lima_dev(struct drm_device *dev)
{
	return dev->dev_private;
}