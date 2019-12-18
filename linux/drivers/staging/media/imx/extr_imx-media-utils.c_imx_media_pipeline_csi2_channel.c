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
struct media_pad {int index; } ;
struct media_entity {int dummy; } ;

/* Variables and functions */
 int EPIPE ; 
 int /*<<< orphan*/  IMX_MEDIA_GRP_ID_CSI2 ; 
 struct media_pad* imx_media_pipeline_pad (struct media_entity*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int imx_media_pipeline_csi2_channel(struct media_entity *start_entity)
{
	struct media_pad *pad;
	int ret = -EPIPE;

	pad = imx_media_pipeline_pad(start_entity, IMX_MEDIA_GRP_ID_CSI2,
				     0, true);
	if (pad)
		ret = pad->index - 1;

	return ret;
}