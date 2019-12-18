#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int ucAction; int /*<<< orphan*/  ucBitPerColor; int /*<<< orphan*/  ucDVOConfig; void* usPixelClock; } ;
struct TYPE_16__ {int ucAction; int /*<<< orphan*/  ucDVOConfig; void* usPixelClock; } ;
struct TYPE_12__ {int /*<<< orphan*/  ucAttribute; } ;
struct TYPE_13__ {TYPE_3__ sDigAttrib; } ;
struct TYPE_14__ {int ucAction; TYPE_4__ usDevAttr; int /*<<< orphan*/  ucDeviceType; void* usPixelClock; } ;
struct TYPE_15__ {TYPE_5__ sDVOEncoder; } ;
struct TYPE_10__ {int ucEnable; int /*<<< orphan*/  ucMisc; } ;
struct TYPE_11__ {TYPE_1__ sXTmdsEncoder; } ;
union dvo_encoder_control {TYPE_8__ dvo_v4; TYPE_7__ dvo_v3; TYPE_6__ dvo; TYPE_2__ ext_tmds; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct amdgpu_encoder {int pixel_clock; } ;
struct TYPE_18__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_9__ mode_info; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DEVICE_DFP1_INDEX ; 
 int /*<<< orphan*/  ATOM_PANEL_MISC_888RGB ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  DVOEncoderControl ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANEL_ENCODER_MISC_DUAL ; 
 int /*<<< orphan*/  amdgpu_atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_get_bpc (struct drm_encoder*) ; 
 int /*<<< orphan*/  amdgpu_dig_monitor_is_duallink (struct drm_encoder*,int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (union dvo_encoder_control*,int /*<<< orphan*/ ,int) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void
amdgpu_atombios_encoder_setup_dvo(struct drm_encoder *encoder, int action)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	union dvo_encoder_control args;
	int index = GetIndexIntoMasterTable(COMMAND, DVOEncoderControl);
	uint8_t frev, crev;

	memset(&args, 0, sizeof(args));

	if (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
		return;

	switch (frev) {
	case 1:
		switch (crev) {
		case 1:
			/* R4xx, R5xx */
			args.ext_tmds.sXTmdsEncoder.ucEnable = action;

			if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
				args.ext_tmds.sXTmdsEncoder.ucMisc |= PANEL_ENCODER_MISC_DUAL;

			args.ext_tmds.sXTmdsEncoder.ucMisc |= ATOM_PANEL_MISC_888RGB;
			break;
		case 2:
			/* RS600/690/740 */
			args.dvo.sDVOEncoder.ucAction = action;
			args.dvo.sDVOEncoder.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_clock / 10);
			/* DFP1, CRT1, TV1 depending on the type of port */
			args.dvo.sDVOEncoder.ucDeviceType = ATOM_DEVICE_DFP1_INDEX;

			if (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_clock))
				args.dvo.sDVOEncoder.usDevAttr.sDigAttrib.ucAttribute |= PANEL_ENCODER_MISC_DUAL;
			break;
		case 3:
			/* R6xx */
			args.dvo_v3.ucAction = action;
			args.dvo_v3.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_clock / 10);
			args.dvo_v3.ucDVOConfig = 0; /* XXX */
			break;
		case 4:
			/* DCE8 */
			args.dvo_v4.ucAction = action;
			args.dvo_v4.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_clock / 10);
			args.dvo_v4.ucDVOConfig = 0; /* XXX */
			args.dvo_v4.ucBitPerColor = amdgpu_atombios_encoder_get_bpc(encoder);
			break;
		default:
			DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
			break;
		}
		break;
	default:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		break;
	}

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uint32_t *)&args);
}