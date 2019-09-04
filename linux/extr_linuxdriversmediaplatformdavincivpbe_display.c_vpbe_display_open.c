#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct vpbe_layer {int /*<<< orphan*/  usrs; int /*<<< orphan*/  opslock; TYPE_2__ layer_info; struct vpbe_display* disp_dev; } ;
struct vpbe_display {struct osd_state* osd_device; struct vpbe_device* vpbe_dev; } ;
struct vpbe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_3__ {int (* request_layer ) (struct osd_state*,int /*<<< orphan*/ ) ;} ;
struct osd_state {TYPE_1__ ops; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct osd_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 struct vpbe_layer* video_drvdata (struct file*) ; 

__attribute__((used)) static int vpbe_display_open(struct file *file)
{
	struct vpbe_layer *layer = video_drvdata(file);
	struct vpbe_display *disp_dev = layer->disp_dev;
	struct vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	struct osd_state *osd_device = disp_dev->osd_device;
	int err;

	/* creating context for file descriptor */
	err = v4l2_fh_open(file);
	if (err) {
		v4l2_err(&vpbe_dev->v4l2_dev, "v4l2_fh_open failed\n");
		return err;
	}

	/* leaving if layer is already initialized */
	if (!v4l2_fh_is_singular_file(file))
		return err;

	if (!layer->usrs) {
		if (mutex_lock_interruptible(&layer->opslock))
			return -ERESTARTSYS;
		/* First claim the layer for this device */
		err = osd_device->ops.request_layer(osd_device,
						layer->layer_info.id);
		mutex_unlock(&layer->opslock);
		if (err < 0) {
			/* Couldn't get layer */
			v4l2_err(&vpbe_dev->v4l2_dev,
				"Display Manager failed to allocate layer\n");
			v4l2_fh_release(file);
			return -EINVAL;
		}
	}
	/* Increment layer usrs counter */
	layer->usrs++;
	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
			"vpbe display device opened successfully\n");
	return 0;
}