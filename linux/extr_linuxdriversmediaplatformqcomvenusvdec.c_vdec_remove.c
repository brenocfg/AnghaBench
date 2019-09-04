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
struct venus_core {int /*<<< orphan*/  dev_dec; int /*<<< orphan*/  vdev_dec; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct venus_core* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdec_remove(struct platform_device *pdev)
{
	struct venus_core *core = dev_get_drvdata(pdev->dev.parent);

	video_unregister_device(core->vdev_dec);
	pm_runtime_disable(core->dev_dec);

	return 0;
}