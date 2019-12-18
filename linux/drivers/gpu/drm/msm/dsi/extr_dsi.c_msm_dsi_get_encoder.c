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
struct msm_dsi {struct drm_encoder* encoder; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_dsi_device_connected (struct msm_dsi*) ; 

struct drm_encoder *msm_dsi_get_encoder(struct msm_dsi *msm_dsi)
{
	if (!msm_dsi || !msm_dsi_device_connected(msm_dsi))
		return NULL;

	return msm_dsi->encoder;
}