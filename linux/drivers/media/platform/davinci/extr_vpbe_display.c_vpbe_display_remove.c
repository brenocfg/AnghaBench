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
struct vpbe_layer {int /*<<< orphan*/  video_dev; } ;
struct vpbe_display {struct vpbe_layer** dev; struct vpbe_device* vpbe_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* deinitialize ) (int /*<<< orphan*/ *,struct vpbe_device*) ;} ;
struct vpbe_device {TYPE_1__ ops; int /*<<< orphan*/  v4l2_dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int VPBE_DISPLAY_MAX_DEVICES ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  kfree (struct vpbe_layer*) ; 
 struct vpbe_display* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct vpbe_device*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vpbe_display_remove(struct platform_device *pdev)
{
	struct vpbe_layer *vpbe_display_layer;
	struct vpbe_display *disp_dev = platform_get_drvdata(pdev);
	struct vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	int i;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "vpbe_display_remove\n");

	/* deinitialize the vpbe display controller */
	if (vpbe_dev->ops.deinitialize)
		vpbe_dev->ops.deinitialize(&pdev->dev, vpbe_dev);
	/* un-register device */
	for (i = 0; i < VPBE_DISPLAY_MAX_DEVICES; i++) {
		/* Get the pointer to the layer object */
		vpbe_display_layer = disp_dev->dev[i];
		/* Unregister video device */
		video_unregister_device(&vpbe_display_layer->video_dev);

	}
	for (i = 0; i < VPBE_DISPLAY_MAX_DEVICES; i++) {
		kfree(disp_dev->dev[i]);
		disp_dev->dev[i] = NULL;
	}

	return 0;
}