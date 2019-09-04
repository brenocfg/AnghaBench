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
struct regmap {int dummy; } ;
struct pl111_drm_dev_private {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static inline int pl111_vexpress_clcd_init(struct device *dev,
					   struct pl111_drm_dev_private *priv,
					   struct regmap *map)
{
	return -ENODEV;
}