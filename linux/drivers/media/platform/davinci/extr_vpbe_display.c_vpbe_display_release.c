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
struct osd_layer_config {scalar_t__ pixfmt; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; struct osd_layer_config config; } ;
struct vpbe_layer {int /*<<< orphan*/  opslock; TYPE_2__ layer_info; int /*<<< orphan*/  usrs; struct vpbe_display* disp_dev; } ;
struct vpbe_display {scalar_t__ cbcr_ofst; struct osd_state* osd_device; struct vpbe_device* vpbe_dev; } ;
struct vpbe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* release_layer ) (struct osd_state*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disable_layer ) (struct osd_state*,int /*<<< orphan*/ ) ;} ;
struct osd_state {TYPE_1__ ops; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ PIXFMT_NV12 ; 
 int /*<<< orphan*/  _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 struct vpbe_layer* _vpbe_display_get_other_win_layer (struct vpbe_display*,struct vpbe_layer*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct osd_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct osd_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct osd_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct osd_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct osd_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct vpbe_layer* video_drvdata (struct file*) ; 

__attribute__((used)) static int vpbe_display_release(struct file *file)
{
	struct vpbe_layer *layer = video_drvdata(file);
	struct osd_layer_config *cfg  = &layer->layer_info.config;
	struct vpbe_display *disp_dev = layer->disp_dev;
	struct vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	struct osd_state *osd_device = disp_dev->osd_device;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "vpbe_display_release\n");

	mutex_lock(&layer->opslock);

	osd_device->ops.disable_layer(osd_device,
			layer->layer_info.id);
	/* Decrement layer usrs counter */
	layer->usrs--;
	/* If this file handle has initialize encoder device, reset it */
	if (!layer->usrs) {
		if (cfg->pixfmt == PIXFMT_NV12) {
			struct vpbe_layer *otherlayer;
			otherlayer =
			_vpbe_display_get_other_win_layer(disp_dev, layer);
			osd_device->ops.disable_layer(osd_device,
					otherlayer->layer_info.id);
			osd_device->ops.release_layer(osd_device,
					otherlayer->layer_info.id);
		}
		osd_device->ops.disable_layer(osd_device,
				layer->layer_info.id);
		osd_device->ops.release_layer(osd_device,
				layer->layer_info.id);
	}

	_vb2_fop_release(file, NULL);
	mutex_unlock(&layer->opslock);

	disp_dev->cbcr_ofst = 0;

	return 0;
}