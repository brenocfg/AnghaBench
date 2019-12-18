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
struct v4l2_flash_config {int dummy; } ;
struct v4l2_flash {int dummy; } ;
struct led_classdev {int dummy; } ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct v4l2_flash* __v4l2_flash_init (struct device*,struct fwnode_handle*,int /*<<< orphan*/ *,struct led_classdev*,int /*<<< orphan*/ *,struct v4l2_flash_config*) ; 

struct v4l2_flash *v4l2_flash_indicator_init(
	struct device *dev, struct fwnode_handle *fwn,
	struct led_classdev *iled_cdev,
	struct v4l2_flash_config *config)
{
	return __v4l2_flash_init(dev, fwn, NULL, iled_cdev, NULL, config);
}