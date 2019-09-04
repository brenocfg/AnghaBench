#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct psb_intel_sdvo_tv_format {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  base; } ;
struct TYPE_8__ {TYPE_3__ base; } ;
struct psb_intel_sdvo_connector {int format_supported_num; int* tv_format_supported; int /*<<< orphan*/  tv_format; TYPE_4__ base; } ;
struct TYPE_5__ {struct drm_device* dev; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
struct psb_intel_sdvo {size_t tv_format_index; TYPE_2__ base; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  format_map ;
typedef  int /*<<< orphan*/  format ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_MODE_PROP_ENUM ; 
 int /*<<< orphan*/  SDVO_CMD_GET_SUPPORTED_TV_FORMATS ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_property_add_enum (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_property_create (struct drm_device*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,struct psb_intel_sdvo_tv_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  psb_intel_sdvo_get_value (struct psb_intel_sdvo*,int /*<<< orphan*/ ,struct psb_intel_sdvo_tv_format*,int) ; 
 int /*<<< orphan*/  psb_intel_sdvo_set_target_output (struct psb_intel_sdvo*,int) ; 
 int /*<<< orphan*/ * tv_format_names ; 

__attribute__((used)) static bool psb_intel_sdvo_tv_create_property(struct psb_intel_sdvo *psb_intel_sdvo,
					  struct psb_intel_sdvo_connector *psb_intel_sdvo_connector,
					  int type)
{
	struct drm_device *dev = psb_intel_sdvo->base.base.dev;
	struct psb_intel_sdvo_tv_format format;
	uint32_t format_map, i;

	if (!psb_intel_sdvo_set_target_output(psb_intel_sdvo, type))
		return false;

	BUILD_BUG_ON(sizeof(format) != 6);
	if (!psb_intel_sdvo_get_value(psb_intel_sdvo,
				  SDVO_CMD_GET_SUPPORTED_TV_FORMATS,
				  &format, sizeof(format)))
		return false;

	memcpy(&format_map, &format, min(sizeof(format_map), sizeof(format)));

	if (format_map == 0)
		return false;

	psb_intel_sdvo_connector->format_supported_num = 0;
	for (i = 0 ; i < ARRAY_SIZE(tv_format_names); i++)
		if (format_map & (1 << i))
			psb_intel_sdvo_connector->tv_format_supported[psb_intel_sdvo_connector->format_supported_num++] = i;


	psb_intel_sdvo_connector->tv_format =
			drm_property_create(dev, DRM_MODE_PROP_ENUM,
					    "mode", psb_intel_sdvo_connector->format_supported_num);
	if (!psb_intel_sdvo_connector->tv_format)
		return false;

	for (i = 0; i < psb_intel_sdvo_connector->format_supported_num; i++)
		drm_property_add_enum(
				psb_intel_sdvo_connector->tv_format,
				i, tv_format_names[psb_intel_sdvo_connector->tv_format_supported[i]]);

	psb_intel_sdvo->tv_format_index = psb_intel_sdvo_connector->tv_format_supported[0];
	drm_object_attach_property(&psb_intel_sdvo_connector->base.base.base,
				      psb_intel_sdvo_connector->tv_format, 0);
	return true;

}