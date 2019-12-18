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
struct TYPE_2__ {int num_pads; struct media_pad* pads; } ;
struct v4l2_subdev {TYPE_1__ entity; } ;
struct media_pad {int flags; } ;
struct internal_subdev {struct internal_pad* pad; } ;
struct internal_pad {int num_links; struct internal_link* link; } ;
struct internal_link {size_t remote; } ;
struct imx_media_dev {struct v4l2_subdev*** sync_sd; } ;

/* Variables and functions */
 int MEDIA_PAD_FL_SOURCE ; 
 int create_internal_link (struct imx_media_dev*,struct v4l2_subdev*,struct v4l2_subdev*,struct internal_link const*) ; 

__attribute__((used)) static int create_ipu_internal_links(struct imx_media_dev *imxmd,
				     const struct internal_subdev *intsd,
				     struct v4l2_subdev *sd,
				     int ipu_id)
{
	const struct internal_pad *intpad;
	const struct internal_link *link;
	struct media_pad *pad;
	int i, j, ret;

	/* create the source->sink links */
	for (i = 0; i < sd->entity.num_pads; i++) {
		intpad = &intsd->pad[i];
		pad = &sd->entity.pads[i];

		if (!(pad->flags & MEDIA_PAD_FL_SOURCE))
			continue;

		for (j = 0; j < intpad->num_links; j++) {
			struct v4l2_subdev *sink;

			link = &intpad->link[j];
			sink = imxmd->sync_sd[ipu_id][link->remote];

			ret = create_internal_link(imxmd, sd, sink, link);
			if (ret)
				return ret;
		}
	}

	return 0;
}