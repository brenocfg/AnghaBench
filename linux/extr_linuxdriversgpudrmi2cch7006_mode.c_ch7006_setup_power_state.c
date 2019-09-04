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
typedef  int uint8_t ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int* regs; } ;
struct ch7006_priv {int select_subconnector; int subconnector; scalar_t__ last_dpms; int chip_version; TYPE_1__ state; } ;

/* Variables and functions */
 size_t CH7006_POWER ; 
 int /*<<< orphan*/  CH7006_POWER_LEVEL ; 
 int CH7006_POWER_RESET ; 
 int CH7006_POWER_SCART ; 
 int /*<<< orphan*/  CVBS_OFF ; 
 scalar_t__ DRM_MODE_DPMS_ON ; 
#define  DRM_MODE_SUBCONNECTOR_Composite 130 
#define  DRM_MODE_SUBCONNECTOR_SCART 129 
#define  DRM_MODE_SUBCONNECTOR_SVIDEO 128 
 int /*<<< orphan*/  FULL_POWER_OFF ; 
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  POWER_OFF ; 
 int /*<<< orphan*/  SVIDEO_OFF ; 
 int bitfs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ch7006_priv* to_ch7006_priv (struct drm_encoder*) ; 

void ch7006_setup_power_state(struct drm_encoder *encoder)
{
	struct ch7006_priv *priv = to_ch7006_priv(encoder);
	uint8_t *power = &priv->state.regs[CH7006_POWER];
	int subconnector;

	subconnector = priv->select_subconnector ? priv->select_subconnector :
							priv->subconnector;

	*power = CH7006_POWER_RESET;

	if (priv->last_dpms == DRM_MODE_DPMS_ON) {
		switch (subconnector) {
		case DRM_MODE_SUBCONNECTOR_SVIDEO:
			*power |= bitfs(CH7006_POWER_LEVEL, CVBS_OFF);
			break;
		case DRM_MODE_SUBCONNECTOR_Composite:
			*power |= bitfs(CH7006_POWER_LEVEL, SVIDEO_OFF);
			break;
		case DRM_MODE_SUBCONNECTOR_SCART:
			*power |= bitfs(CH7006_POWER_LEVEL, NORMAL) |
				CH7006_POWER_SCART;
			break;
		}

	} else {
		if (priv->chip_version >= 0x20)
			*power |= bitfs(CH7006_POWER_LEVEL, FULL_POWER_OFF);
		else
			*power |= bitfs(CH7006_POWER_LEVEL, POWER_OFF);
	}
}