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
typedef  int /*<<< orphan*/  uint8_t ;
struct qxl_release {int dummy; } ;
struct qxl_drm_image {int dummy; } ;
struct qxl_device {int dummy; } ;

/* Variables and functions */
 int qxl_image_init_helper (struct qxl_device*,struct qxl_release*,struct qxl_drm_image*,int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ ,int) ; 

int qxl_image_init(struct qxl_device *qdev,
		     struct qxl_release *release,
		     struct qxl_drm_image *dimage,
		     const uint8_t *data,
		     int x, int y, int width, int height,
		     int depth, int stride)
{
	data += y * stride + x * (depth / 8);
	return qxl_image_init_helper(qdev, release, dimage, data,
				       width, height, depth, 0, stride);
}