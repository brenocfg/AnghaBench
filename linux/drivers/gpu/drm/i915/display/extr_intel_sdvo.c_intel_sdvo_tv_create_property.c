#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_sdvo_tv_format {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  base; TYPE_4__* state; } ;
struct TYPE_12__ {TYPE_5__ base; } ;
struct intel_sdvo_connector {int format_supported_num; int* tv_format_supported; int /*<<< orphan*/  tv_format; TYPE_6__ base; } ;
struct TYPE_7__ {struct drm_device* dev; } ;
struct TYPE_8__ {TYPE_1__ base; } ;
struct intel_sdvo {TYPE_2__ base; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  format_map ;
typedef  int /*<<< orphan*/  format ;
struct TYPE_9__ {size_t mode; } ;
struct TYPE_10__ {TYPE_3__ tv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_MODE_PROP_ENUM ; 
 int /*<<< orphan*/  SDVO_CMD_GET_SUPPORTED_TV_FORMATS ; 
 int TV_FORMAT_NUM ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_property_add_enum (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_property_create (struct drm_device*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  intel_sdvo_get_value (struct intel_sdvo*,int /*<<< orphan*/ ,struct intel_sdvo_tv_format*,int) ; 
 int /*<<< orphan*/  intel_sdvo_set_target_output (struct intel_sdvo*,int) ; 
 int /*<<< orphan*/  memcpy (int*,struct intel_sdvo_tv_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/ * tv_format_names ; 

__attribute__((used)) static bool intel_sdvo_tv_create_property(struct intel_sdvo *intel_sdvo,
					  struct intel_sdvo_connector *intel_sdvo_connector,
					  int type)
{
	struct drm_device *dev = intel_sdvo->base.base.dev;
	struct intel_sdvo_tv_format format;
	u32 format_map, i;

	if (!intel_sdvo_set_target_output(intel_sdvo, type))
		return false;

	BUILD_BUG_ON(sizeof(format) != 6);
	if (!intel_sdvo_get_value(intel_sdvo,
				  SDVO_CMD_GET_SUPPORTED_TV_FORMATS,
				  &format, sizeof(format)))
		return false;

	memcpy(&format_map, &format, min(sizeof(format_map), sizeof(format)));

	if (format_map == 0)
		return false;

	intel_sdvo_connector->format_supported_num = 0;
	for (i = 0 ; i < TV_FORMAT_NUM; i++)
		if (format_map & (1 << i))
			intel_sdvo_connector->tv_format_supported[intel_sdvo_connector->format_supported_num++] = i;


	intel_sdvo_connector->tv_format =
			drm_property_create(dev, DRM_MODE_PROP_ENUM,
					    "mode", intel_sdvo_connector->format_supported_num);
	if (!intel_sdvo_connector->tv_format)
		return false;

	for (i = 0; i < intel_sdvo_connector->format_supported_num; i++)
		drm_property_add_enum(intel_sdvo_connector->tv_format, i,
				      tv_format_names[intel_sdvo_connector->tv_format_supported[i]]);

	intel_sdvo_connector->base.base.state->tv.mode = intel_sdvo_connector->tv_format_supported[0];
	drm_object_attach_property(&intel_sdvo_connector->base.base.base,
				   intel_sdvo_connector->tv_format, 0);
	return true;

}