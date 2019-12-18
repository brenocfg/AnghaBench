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
struct qxl_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct qxl_bo {TYPE_1__ surf; } ;

/* Variables and functions */
 int qxl_check_mode (struct qxl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qxl_check_framebuffer(struct qxl_device *qdev,
				 struct qxl_bo *bo)
{
	return qxl_check_mode(qdev, bo->surf.width, bo->surf.height);
}