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
struct omap_encoder {struct omap_dss_device* dssdev; } ;
struct omap_dss_device {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 struct omap_encoder* to_omap_encoder (struct drm_encoder*) ; 

struct omap_dss_device *omap_encoder_get_dssdev(struct drm_encoder *encoder)
{
	struct omap_encoder *omap_encoder = to_omap_encoder(encoder);

	return omap_encoder->dssdev;
}