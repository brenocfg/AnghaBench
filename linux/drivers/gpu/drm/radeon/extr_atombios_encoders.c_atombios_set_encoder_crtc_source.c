#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ucCRTC; void* ucEncoderID; void* ucEncodeMode; } ;
struct TYPE_4__ {int ucCRTC; void* ucDevice; } ;
union crtc_source_param {TYPE_2__ v2; TYPE_1__ v1; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_encoder_atom_dig {int /*<<< orphan*/  dig_encoder; } ;
struct radeon_encoder {int encoder_id; int devices; int active_device; struct radeon_encoder_atom_dig* enc_priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_3__ mode_info; } ;
struct radeon_crtc {int crtc_id; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {int /*<<< orphan*/  connector_type; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 void* ASIC_INT_DAC1_ENCODER_ID ; 
 void* ASIC_INT_DAC2_ENCODER_ID ; 
 void* ASIC_INT_DIG1_ENCODER_ID ; 
 void* ASIC_INT_DIG2_ENCODER_ID ; 
 void* ASIC_INT_DIG3_ENCODER_ID ; 
 void* ASIC_INT_DIG4_ENCODER_ID ; 
 void* ASIC_INT_DIG5_ENCODER_ID ; 
 void* ASIC_INT_DIG6_ENCODER_ID ; 
 void* ASIC_INT_DIG7_ENCODER_ID ; 
 void* ASIC_INT_DVO_ENCODER_ID ; 
 void* ASIC_INT_TV_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_IS_AVIVO (struct radeon_device*) ; 
 void* ATOM_DEVICE_CRT1_INDEX ; 
 void* ATOM_DEVICE_CRT2_INDEX ; 
 void* ATOM_DEVICE_CV_INDEX ; 
 int ATOM_DEVICE_CV_SUPPORT ; 
 void* ATOM_DEVICE_DFP1_INDEX ; 
 void* ATOM_DEVICE_DFP2_INDEX ; 
 void* ATOM_DEVICE_DFP3_INDEX ; 
 void* ATOM_DEVICE_LCD1_INDEX ; 
 int ATOM_DEVICE_LCD1_SUPPORT ; 
 int ATOM_DEVICE_LCD_SUPPORT ; 
 void* ATOM_DEVICE_TV1_INDEX ; 
 int ATOM_DEVICE_TV_SUPPORT ; 
 void* ATOM_ENCODER_MODE_CRT ; 
 void* ATOM_ENCODER_MODE_LVDS ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_LVDS ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VGA ; 
#define  ENCODER_OBJECT_ID_INTERNAL_DAC1 143 
#define  ENCODER_OBJECT_ID_INTERNAL_DAC2 142 
#define  ENCODER_OBJECT_ID_INTERNAL_DDI 141 
#define  ENCODER_OBJECT_ID_INTERNAL_DVO1 140 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1 139 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2 138 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1 137 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA 136 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1 135 
#define  ENCODER_OBJECT_ID_INTERNAL_LVDS 134 
#define  ENCODER_OBJECT_ID_INTERNAL_LVTM1 133 
#define  ENCODER_OBJECT_ID_INTERNAL_TMDS1 132 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY 131 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY1 130 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY2 129 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY3 128 
 int /*<<< orphan*/  ENCODER_OBJECT_ID_NONE ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectCRTC_Source ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 void* atombios_get_encoder_mode (struct drm_encoder*) ; 
 int /*<<< orphan*/  memset (union crtc_source_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_atombios_encoder_crtc_scratch_regs (struct drm_encoder*,int) ; 
 int /*<<< orphan*/  radeon_encoder_get_dp_bridge_encoder_id (struct drm_encoder*) ; 
 struct drm_connector* radeon_get_connector_for_encoder (struct drm_encoder*) ; 
 struct radeon_crtc* to_radeon_crtc (int /*<<< orphan*/ ) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void
atombios_set_encoder_crtc_source(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	union crtc_source_param args;
	int index = GetIndexIntoMasterTable(COMMAND, SelectCRTC_Source);
	uint8_t frev, crev;
	struct radeon_encoder_atom_dig *dig;

	memset(&args, 0, sizeof(args));

	if (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		return;

	switch (frev) {
	case 1:
		switch (crev) {
		case 1:
		default:
			if (ASIC_IS_AVIVO(rdev))
				args.v1.ucCRTC = radeon_crtc->crtc_id;
			else {
				if (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_DAC1) {
					args.v1.ucCRTC = radeon_crtc->crtc_id;
				} else {
					args.v1.ucCRTC = radeon_crtc->crtc_id << 2;
				}
			}
			switch (radeon_encoder->encoder_id) {
			case ENCODER_OBJECT_ID_INTERNAL_TMDS1:
			case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
				args.v1.ucDevice = ATOM_DEVICE_DFP1_INDEX;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_LVDS:
			case ENCODER_OBJECT_ID_INTERNAL_LVTM1:
				if (radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT)
					args.v1.ucDevice = ATOM_DEVICE_LCD1_INDEX;
				else
					args.v1.ucDevice = ATOM_DEVICE_DFP3_INDEX;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_DVO1:
			case ENCODER_OBJECT_ID_INTERNAL_DDI:
			case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
				args.v1.ucDevice = ATOM_DEVICE_DFP2_INDEX;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_DAC1:
			case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
				if (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v1.ucDevice = ATOM_DEVICE_TV1_INDEX;
				else if (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v1.ucDevice = ATOM_DEVICE_CV_INDEX;
				else
					args.v1.ucDevice = ATOM_DEVICE_CRT1_INDEX;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_DAC2:
			case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
				if (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v1.ucDevice = ATOM_DEVICE_TV1_INDEX;
				else if (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v1.ucDevice = ATOM_DEVICE_CV_INDEX;
				else
					args.v1.ucDevice = ATOM_DEVICE_CRT2_INDEX;
				break;
			}
			break;
		case 2:
			args.v2.ucCRTC = radeon_crtc->crtc_id;
			if (radeon_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE) {
				struct drm_connector *connector = radeon_get_connector_for_encoder(encoder);

				if (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)
					args.v2.ucEncodeMode = ATOM_ENCODER_MODE_LVDS;
				else if (connector->connector_type == DRM_MODE_CONNECTOR_VGA)
					args.v2.ucEncodeMode = ATOM_ENCODER_MODE_CRT;
				else
					args.v2.ucEncodeMode = atombios_get_encoder_mode(encoder);
			} else if (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) {
				args.v2.ucEncodeMode = ATOM_ENCODER_MODE_LVDS;
			} else {
				args.v2.ucEncodeMode = atombios_get_encoder_mode(encoder);
			}
			switch (radeon_encoder->encoder_id) {
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
			case ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
			case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
				dig = radeon_encoder->enc_priv;
				switch (dig->dig_encoder) {
				case 0:
					args.v2.ucEncoderID = ASIC_INT_DIG1_ENCODER_ID;
					break;
				case 1:
					args.v2.ucEncoderID = ASIC_INT_DIG2_ENCODER_ID;
					break;
				case 2:
					args.v2.ucEncoderID = ASIC_INT_DIG3_ENCODER_ID;
					break;
				case 3:
					args.v2.ucEncoderID = ASIC_INT_DIG4_ENCODER_ID;
					break;
				case 4:
					args.v2.ucEncoderID = ASIC_INT_DIG5_ENCODER_ID;
					break;
				case 5:
					args.v2.ucEncoderID = ASIC_INT_DIG6_ENCODER_ID;
					break;
				case 6:
					args.v2.ucEncoderID = ASIC_INT_DIG7_ENCODER_ID;
					break;
				}
				break;
			case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
				args.v2.ucEncoderID = ASIC_INT_DVO_ENCODER_ID;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
				if (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v2.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				else if (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v2.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				else
					args.v2.ucEncoderID = ASIC_INT_DAC1_ENCODER_ID;
				break;
			case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
				if (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v2.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				else if (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v2.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				else
					args.v2.ucEncoderID = ASIC_INT_DAC2_ENCODER_ID;
				break;
			}
			break;
		}
		break;
	default:
		DRM_ERROR("Unknown table version: %d, %d\n", frev, crev);
		return;
	}

	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);

	/* update scratch regs with new routing */
	radeon_atombios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
}