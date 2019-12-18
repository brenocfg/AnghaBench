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
struct drm_property_blob {scalar_t__ length; int /*<<< orphan*/  data; } ;
struct drm_connector_state {struct drm_property_blob* hdr_output_metadata; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
is_hdr_metadata_different(const struct drm_connector_state *old_state,
			  const struct drm_connector_state *new_state)
{
	struct drm_property_blob *old_blob = old_state->hdr_output_metadata;
	struct drm_property_blob *new_blob = new_state->hdr_output_metadata;

	if (old_blob != new_blob) {
		if (old_blob && new_blob &&
		    old_blob->length == new_blob->length)
			return memcmp(old_blob->data, new_blob->data,
				      old_blob->length);

		return true;
	}

	return false;
}