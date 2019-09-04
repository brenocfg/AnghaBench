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
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct omap_vout_device {scalar_t__ dss_mode; int /*<<< orphan*/  bpp; TYPE_1__ pix; int /*<<< orphan*/ * smsshado_phy_addr; int /*<<< orphan*/ * vrfb_context; int /*<<< orphan*/  vrfb_static_allocation; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ OMAP_DSS_COLOR_UYVY ; 
 scalar_t__ OMAP_DSS_COLOR_YUV2 ; 
 unsigned int VRFB_NUM_BUFS ; 
 int /*<<< orphan*/  is_rotation_enabled (struct omap_vout_device*) ; 
 scalar_t__ omap_vout_allocate_vrfb_buffers (struct omap_vout_device*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  omap_vrfb_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int omap_vout_vrfb_buffer_setup(struct omap_vout_device *vout,
			  unsigned int *count, unsigned int startindex)
{
	int i;
	bool yuv_mode;

	if (!is_rotation_enabled(vout))
		return 0;

	/* If rotation is enabled, allocate memory for VRFB space also */
	*count = *count > VRFB_NUM_BUFS ? VRFB_NUM_BUFS : *count;

	/* Allocate the VRFB buffers only if the buffers are not
	 * allocated during init time.
	 */
	if (!vout->vrfb_static_allocation)
		if (omap_vout_allocate_vrfb_buffers(vout, count, startindex))
			return -ENOMEM;

	if (vout->dss_mode == OMAP_DSS_COLOR_YUV2 ||
			vout->dss_mode == OMAP_DSS_COLOR_UYVY)
		yuv_mode = true;
	else
		yuv_mode = false;

	for (i = 0; i < *count; i++)
		omap_vrfb_setup(&vout->vrfb_context[i],
				vout->smsshado_phy_addr[i], vout->pix.width,
				vout->pix.height, vout->bpp, yuv_mode);

	return 0;
}