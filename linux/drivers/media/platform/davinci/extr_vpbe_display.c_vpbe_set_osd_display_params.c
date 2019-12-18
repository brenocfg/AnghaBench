#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct osd_layer_config {scalar_t__ pixfmt; } ;
struct TYPE_8__ {int enable; int /*<<< orphan*/  id; struct osd_layer_config config; } ;
struct vpbe_layer {TYPE_4__ layer_info; TYPE_2__* cur_frm; } ;
struct vpbe_display {int /*<<< orphan*/  cbcr_ofst; struct vpbe_device* vpbe_dev; struct osd_state* osd_device; } ;
struct vpbe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_7__ {int (* enable_layer ) (struct osd_state*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* start_layer ) (struct osd_state*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ;} ;
struct osd_state {TYPE_3__ ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_6__ {TYPE_1__ vb; } ;

/* Variables and functions */
 scalar_t__ PIXFMT_NV12 ; 
 struct vpbe_layer* _vpbe_display_get_other_win_layer (struct vpbe_display*,struct vpbe_layer*) ; 
 int /*<<< orphan*/  stub1 (struct osd_state*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int stub2 (struct osd_state*,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct osd_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpbe_set_osd_display_params(struct vpbe_display *disp_dev,
			struct vpbe_layer *layer)
{
	struct osd_layer_config *cfg  = &layer->layer_info.config;
	struct osd_state *osd_device = disp_dev->osd_device;
	struct vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	unsigned long addr;
	int ret;

	addr = vb2_dma_contig_plane_dma_addr(&layer->cur_frm->vb.vb2_buf, 0);
	/* Set address in the display registers */
	osd_device->ops.start_layer(osd_device,
				    layer->layer_info.id,
				    addr,
				    disp_dev->cbcr_ofst);

	ret = osd_device->ops.enable_layer(osd_device,
				layer->layer_info.id, 0);
	if (ret < 0) {
		v4l2_err(&vpbe_dev->v4l2_dev,
			"Error in enabling osd window layer 0\n");
		return -1;
	}

	/* Enable the window */
	layer->layer_info.enable = 1;
	if (cfg->pixfmt == PIXFMT_NV12) {
		struct vpbe_layer *otherlayer =
			_vpbe_display_get_other_win_layer(disp_dev, layer);

		ret = osd_device->ops.enable_layer(osd_device,
				otherlayer->layer_info.id, 1);
		if (ret < 0) {
			v4l2_err(&vpbe_dev->v4l2_dev,
				"Error in enabling osd window layer 1\n");
			return -1;
		}
		otherlayer->layer_info.enable = 1;
	}
	return 0;
}