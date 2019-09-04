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
struct omap_encoder {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  kfree (struct omap_encoder*) ; 
 struct omap_encoder* to_omap_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void omap_encoder_destroy(struct drm_encoder *encoder)
{
	struct omap_encoder *omap_encoder = to_omap_encoder(encoder);

	drm_encoder_cleanup(encoder);
	kfree(omap_encoder);
}