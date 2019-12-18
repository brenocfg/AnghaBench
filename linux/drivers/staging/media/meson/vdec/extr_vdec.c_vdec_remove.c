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
struct platform_device {int dummy; } ;
struct amvdec_core {int /*<<< orphan*/  vdev_dec; } ;

/* Variables and functions */
 struct amvdec_core* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdec_remove(struct platform_device *pdev)
{
	struct amvdec_core *core = platform_get_drvdata(pdev);

	video_unregister_device(core->vdev_dec);

	return 0;
}