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
typedef  int /*<<< orphan*/  u8 ;
struct radeon_encoder {TYPE_1__* audio; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_speaker_allocation ) (struct drm_encoder*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int drm_edid_to_speaker_allocation (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_connector_edid (struct drm_connector*) ; 
 struct drm_connector* radeon_get_connector_for_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*,int /*<<< orphan*/ *,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void radeon_audio_write_speaker_allocation(struct drm_encoder *encoder)
{
	struct drm_connector *connector = radeon_get_connector_for_encoder(encoder);
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	u8 *sadb = NULL;
	int sad_count;

	if (!connector)
		return;

	sad_count = drm_edid_to_speaker_allocation(radeon_connector_edid(connector),
						   &sadb);
	if (sad_count < 0) {
		DRM_DEBUG("Couldn't read Speaker Allocation Data Block: %d\n",
			  sad_count);
		sad_count = 0;
	}

	if (radeon_encoder->audio && radeon_encoder->audio->write_speaker_allocation)
		radeon_encoder->audio->write_speaker_allocation(encoder, sadb, sad_count);

	kfree(sadb);
}