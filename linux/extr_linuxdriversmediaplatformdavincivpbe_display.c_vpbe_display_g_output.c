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
struct vpbe_layer {TYPE_1__* disp_dev; } ;
struct vpbe_device {unsigned int current_out_index; int /*<<< orphan*/  v4l2_dev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct vpbe_device* vpbe_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct vpbe_layer* video_drvdata (struct file*) ; 

__attribute__((used)) static int vpbe_display_g_output(struct file *file, void *priv,
				unsigned int *i)
{
	struct vpbe_layer *layer = video_drvdata(file);
	struct vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "VIDIOC_G_OUTPUT\n");
	/* Get the standard from the current encoder */
	*i = vpbe_dev->current_out_index;

	return 0;
}