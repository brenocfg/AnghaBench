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
struct drm_connector {int /*<<< orphan*/  connector_type; } ;
struct drm_cmdline_mode {int interlace; int margins; void* force; } ;

/* Variables and functions */
 void* DRM_FORCE_OFF ; 
 void* DRM_FORCE_ON ; 
 void* DRM_FORCE_ON_DIGITAL ; 
 void* DRM_FORCE_UNSPECIFIED ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DVII ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_HDMIB ; 
 int EINVAL ; 

__attribute__((used)) static int drm_mode_parse_cmdline_extra(const char *str, int length,
					bool freestanding,
					const struct drm_connector *connector,
					struct drm_cmdline_mode *mode)
{
	int i;

	for (i = 0; i < length; i++) {
		switch (str[i]) {
		case 'i':
			if (freestanding)
				return -EINVAL;

			mode->interlace = true;
			break;
		case 'm':
			if (freestanding)
				return -EINVAL;

			mode->margins = true;
			break;
		case 'D':
			if (mode->force != DRM_FORCE_UNSPECIFIED)
				return -EINVAL;

			if ((connector->connector_type != DRM_MODE_CONNECTOR_DVII) &&
			    (connector->connector_type != DRM_MODE_CONNECTOR_HDMIB))
				mode->force = DRM_FORCE_ON;
			else
				mode->force = DRM_FORCE_ON_DIGITAL;
			break;
		case 'd':
			if (mode->force != DRM_FORCE_UNSPECIFIED)
				return -EINVAL;

			mode->force = DRM_FORCE_OFF;
			break;
		case 'e':
			if (mode->force != DRM_FORCE_UNSPECIFIED)
				return -EINVAL;

			mode->force = DRM_FORCE_ON;
			break;
		default:
			return -EINVAL;
		}
	}

	return 0;
}