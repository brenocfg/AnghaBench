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
struct radeon_encoder {TYPE_1__* audio; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector {int dummy; } ;
struct cea_sad {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_sad_regs ) (struct drm_encoder*,struct cea_sad*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int drm_edid_to_sad (int /*<<< orphan*/ ,struct cea_sad**) ; 
 int /*<<< orphan*/  kfree (struct cea_sad*) ; 
 int /*<<< orphan*/  radeon_connector_edid (struct drm_connector*) ; 
 struct drm_connector* radeon_get_connector_for_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*,struct cea_sad*,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void radeon_audio_write_sad_regs(struct drm_encoder *encoder)
{
	struct drm_connector *connector = radeon_get_connector_for_encoder(encoder);
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct cea_sad *sads;
	int sad_count;

	if (!connector)
		return;

	sad_count = drm_edid_to_sad(radeon_connector_edid(connector), &sads);
	if (sad_count <= 0) {
		DRM_ERROR("Couldn't read SADs: %d\n", sad_count);
		return;
	}
	BUG_ON(!sads);

	if (radeon_encoder->audio && radeon_encoder->audio->write_sad_regs)
		radeon_encoder->audio->write_sad_regs(encoder, sads, sad_count);

	kfree(sads);
}