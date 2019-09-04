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
typedef  int /*<<< orphan*/  u64 ;
struct drm_device {int /*<<< orphan*/  dev; struct atmel_hlcdc_dc* dev_private; } ;
struct atmel_hlcdc_layer_desc {scalar_t__ type; } ;
struct atmel_hlcdc_dma_channel_dscr {int dummy; } ;
struct atmel_hlcdc_dc {int /*<<< orphan*/  dscrpool; TYPE_1__* desc; } ;
struct TYPE_2__ {int nlayers; struct atmel_hlcdc_layer_desc* layers; } ;

/* Variables and functions */
 scalar_t__ ATMEL_HLCDC_BASE_LAYER ; 
 scalar_t__ ATMEL_HLCDC_CURSOR_LAYER ; 
 scalar_t__ ATMEL_HLCDC_OVERLAY_LAYER ; 
 int ENOMEM ; 
 int atmel_hlcdc_plane_create (struct drm_device*,struct atmel_hlcdc_layer_desc const*) ; 
 int /*<<< orphan*/  dmam_pool_create (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

int atmel_hlcdc_create_planes(struct drm_device *dev)
{
	struct atmel_hlcdc_dc *dc = dev->dev_private;
	const struct atmel_hlcdc_layer_desc *descs = dc->desc->layers;
	int nlayers = dc->desc->nlayers;
	int i, ret;

	dc->dscrpool = dmam_pool_create("atmel-hlcdc-dscr", dev->dev,
				sizeof(struct atmel_hlcdc_dma_channel_dscr),
				sizeof(u64), 0);
	if (!dc->dscrpool)
		return -ENOMEM;

	for (i = 0; i < nlayers; i++) {
		if (descs[i].type != ATMEL_HLCDC_BASE_LAYER &&
		    descs[i].type != ATMEL_HLCDC_OVERLAY_LAYER &&
		    descs[i].type != ATMEL_HLCDC_CURSOR_LAYER)
			continue;

		ret = atmel_hlcdc_plane_create(dev, &descs[i]);
		if (ret)
			return ret;
	}

	return 0;
}