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
struct drm_device {struct ast_private* dev_private; } ;
struct ast_private {TYPE_1__* fbdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_set_suspend (int /*<<< orphan*/ *,int) ; 

void ast_fbdev_set_suspend(struct drm_device *dev, int state)
{
	struct ast_private *ast = dev->dev_private;

	if (!ast->fbdev)
		return;

	drm_fb_helper_set_suspend(&ast->fbdev->helper, state);
}