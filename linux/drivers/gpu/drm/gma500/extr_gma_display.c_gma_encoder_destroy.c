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
struct gma_encoder {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  kfree (struct gma_encoder*) ; 
 struct gma_encoder* to_gma_encoder (struct drm_encoder*) ; 

void gma_encoder_destroy(struct drm_encoder *encoder)
{
	struct gma_encoder *intel_encoder = to_gma_encoder(encoder);

	drm_encoder_cleanup(encoder);
	kfree(intel_encoder);
}