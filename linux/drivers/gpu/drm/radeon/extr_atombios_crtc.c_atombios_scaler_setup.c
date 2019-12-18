#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_encoder_atom_dac {int tv_std; } ;
struct radeon_encoder {int active_device; struct radeon_encoder_atom_dac* enc_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {scalar_t__ family; TYPE_1__ mode_info; } ;
struct radeon_crtc {int rmx_type; scalar_t__ crtc_id; int /*<<< orphan*/  encoder; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  enum radeon_tv_std { ____Placeholder_radeon_tv_std } radeon_tv_std ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_5__ {void* ucEnable; void* ucTVStandard; scalar_t__ ucScaler; } ;
typedef  TYPE_2__ ENABLE_SCALER_PS_ALLOCATION ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 int ATOM_DEVICE_TV_SUPPORT ; 
 void* ATOM_SCALER_CENTER ; 
 void* ATOM_SCALER_DISABLE ; 
 void* ATOM_SCALER_EXPANSION ; 
 void* ATOM_TV_CV ; 
 void* ATOM_TV_NTSC ; 
 void* ATOM_TV_NTSCJ ; 
 void* ATOM_TV_PAL ; 
 void* ATOM_TV_PAL60 ; 
 void* ATOM_TV_PALCN ; 
 void* ATOM_TV_PALM ; 
 void* ATOM_TV_SECAM ; 
 scalar_t__ CHIP_R580 ; 
 scalar_t__ CHIP_RV515 ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  EnableScaler ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  RMX_ASPECT 138 
#define  RMX_CENTER 137 
#define  RMX_FULL 136 
 void* SCALER_ENABLE_MULTITAP_MODE ; 
#define  TV_STD_NTSC 135 
#define  TV_STD_NTSC_J 134 
#define  TV_STD_PAL 133 
#define  TV_STD_PAL_60 132 
#define  TV_STD_PAL_CN 131 
#define  TV_STD_PAL_M 130 
#define  TV_STD_SCART_PAL 129 
#define  TV_STD_SECAM 128 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atom_rv515_force_tv_scaler (struct radeon_device*,struct radeon_crtc*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 
 struct radeon_encoder* to_radeon_encoder (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atombios_scaler_setup(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	ENABLE_SCALER_PS_ALLOCATION args;
	int index = GetIndexIntoMasterTable(COMMAND, EnableScaler);
	struct radeon_encoder *radeon_encoder =
		to_radeon_encoder(radeon_crtc->encoder);
	/* fixme - fill in enc_priv for atom dac */
	enum radeon_tv_std tv_std = TV_STD_NTSC;
	bool is_tv = false, is_cv = false;

	if (!ASIC_IS_AVIVO(rdev) && radeon_crtc->crtc_id)
		return;

	if (radeon_encoder->active_device & ATOM_DEVICE_TV_SUPPORT) {
		struct radeon_encoder_atom_dac *tv_dac = radeon_encoder->enc_priv;
		tv_std = tv_dac->tv_std;
		is_tv = true;
	}

	memset(&args, 0, sizeof(args));

	args.ucScaler = radeon_crtc->crtc_id;

	if (is_tv) {
		switch (tv_std) {
		case TV_STD_NTSC:
		default:
			args.ucTVStandard = ATOM_TV_NTSC;
			break;
		case TV_STD_PAL:
			args.ucTVStandard = ATOM_TV_PAL;
			break;
		case TV_STD_PAL_M:
			args.ucTVStandard = ATOM_TV_PALM;
			break;
		case TV_STD_PAL_60:
			args.ucTVStandard = ATOM_TV_PAL60;
			break;
		case TV_STD_NTSC_J:
			args.ucTVStandard = ATOM_TV_NTSCJ;
			break;
		case TV_STD_SCART_PAL:
			args.ucTVStandard = ATOM_TV_PAL; /* ??? */
			break;
		case TV_STD_SECAM:
			args.ucTVStandard = ATOM_TV_SECAM;
			break;
		case TV_STD_PAL_CN:
			args.ucTVStandard = ATOM_TV_PALCN;
			break;
		}
		args.ucEnable = SCALER_ENABLE_MULTITAP_MODE;
	} else if (is_cv) {
		args.ucTVStandard = ATOM_TV_CV;
		args.ucEnable = SCALER_ENABLE_MULTITAP_MODE;
	} else {
		switch (radeon_crtc->rmx_type) {
		case RMX_FULL:
			args.ucEnable = ATOM_SCALER_EXPANSION;
			break;
		case RMX_CENTER:
			args.ucEnable = ATOM_SCALER_CENTER;
			break;
		case RMX_ASPECT:
			args.ucEnable = ATOM_SCALER_EXPANSION;
			break;
		default:
			if (ASIC_IS_AVIVO(rdev))
				args.ucEnable = ATOM_SCALER_DISABLE;
			else
				args.ucEnable = ATOM_SCALER_CENTER;
			break;
		}
	}
	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
	if ((is_tv || is_cv)
	    && rdev->family >= CHIP_RV515 && rdev->family <= CHIP_R580) {
		atom_rv515_force_tv_scaler(rdev, radeon_crtc);
	}
}