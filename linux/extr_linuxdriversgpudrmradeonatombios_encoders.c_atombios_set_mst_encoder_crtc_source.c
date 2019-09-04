#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ucEncoderID; int /*<<< orphan*/  ucEncodeMode; int /*<<< orphan*/  ucCRTC; } ;
union crtc_source_param {TYPE_1__ v2; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_2__ mode_info; } ;
struct radeon_crtc {int /*<<< orphan*/  crtc_id; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_INT_DIG1_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_INT_DIG2_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_INT_DIG3_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_INT_DIG4_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_INT_DIG5_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_INT_DIG6_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_INT_DIG7_ENCODER_ID ; 
 int /*<<< orphan*/  ATOM_ENCODER_MODE_DP_MST ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectCRTC_Source ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  memset (union crtc_source_param*,int /*<<< orphan*/ ,int) ; 
 struct radeon_crtc* to_radeon_crtc (int /*<<< orphan*/ ) ; 

void
atombios_set_mst_encoder_crtc_source(struct drm_encoder *encoder, int fe)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	int index = GetIndexIntoMasterTable(COMMAND, SelectCRTC_Source);
	uint8_t frev, crev;
	union crtc_source_param args;

	memset(&args, 0, sizeof(args));

	if (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		return;

	if (frev != 1 && crev != 2)
		DRM_ERROR("Unknown table for MST %d, %d\n", frev, crev);

	args.v2.ucCRTC = radeon_crtc->crtc_id;
	args.v2.ucEncodeMode = ATOM_ENCODER_MODE_DP_MST;

	switch (fe) {
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
	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
}