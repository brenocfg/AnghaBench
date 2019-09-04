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
struct TYPE_6__ {int ucAction; } ;
union dig_transmitter_control {TYPE_2__ v1; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_connector {scalar_t__ connector_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_3__ mode_info; } ;
struct TYPE_8__ {int /*<<< orphan*/  hpd; } ;
struct TYPE_5__ {struct drm_device* dev; } ;
struct amdgpu_connector {TYPE_4__ hpd; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int ATOM_TRANSMITTER_ACTION_POWER_OFF ; 
 int ATOM_TRANSMITTER_ACTION_POWER_ON ; 
 int /*<<< orphan*/  COMMAND ; 
 scalar_t__ DRM_MODE_CONNECTOR_eDP ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIPHYTransmitterControl ; 
 int /*<<< orphan*/  amdgpu_atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_atom_parse_cmd_header (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ amdgpu_display_hpd_sense (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memset (union dig_transmitter_control*,int /*<<< orphan*/ ,int) ; 
 struct amdgpu_connector* to_amdgpu_connector (struct drm_connector*) ; 

bool
amdgpu_atombios_encoder_set_edp_panel_power(struct drm_connector *connector,
				     int action)
{
	struct amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	struct drm_device *dev = amdgpu_connector->base.dev;
	struct amdgpu_device *adev = dev->dev_private;
	union dig_transmitter_control args;
	int index = GetIndexIntoMasterTable(COMMAND, UNIPHYTransmitterControl);
	uint8_t frev, crev;

	if (connector->connector_type != DRM_MODE_CONNECTOR_eDP)
		goto done;

	if ((action != ATOM_TRANSMITTER_ACTION_POWER_ON) &&
	    (action != ATOM_TRANSMITTER_ACTION_POWER_OFF))
		goto done;

	if (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
		goto done;

	memset(&args, 0, sizeof(args));

	args.v1.ucAction = action;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uint32_t *)&args);

	/* wait for the panel to power up */
	if (action == ATOM_TRANSMITTER_ACTION_POWER_ON) {
		int i;

		for (i = 0; i < 300; i++) {
			if (amdgpu_display_hpd_sense(adev, amdgpu_connector->hpd.hpd))
				return true;
			mdelay(1);
		}
		return false;
	}
done:
	return true;
}