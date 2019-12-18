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
struct TYPE_12__ {int ucRefDiv; int ucPostDiv; int ucTransmitterID; int ucEncoderMode; int ucPpll; int /*<<< orphan*/  ucMiscInfo; void* ulFbDivDecFrac; void* usFbDiv; void* ulDispEngClkFreq; } ;
struct TYPE_11__ {int ucCRTC; int ucRefDiv; int ucPostDiv; int ucTransmitterID; int ucEncoderMode; int ucPpll; int /*<<< orphan*/  ucMiscInfo; void* ulFbDivDecFrac; void* usFbDiv; void* usPixelClock; } ;
struct TYPE_10__ {int ucFracFbDiv; int ucPostDiv; int ucPpll; int ucTransmitterId; int ucEncoderMode; int /*<<< orphan*/  ucMiscInfo; void* usFbDiv; void* usRefDiv; void* usPixelClock; } ;
struct TYPE_9__ {int ucFracFbDiv; int ucPostDiv; int ucPpll; int ucCRTC; int ucRefDivSrc; void* usFbDiv; void* usRefDiv; void* usPixelClock; } ;
struct TYPE_8__ {int ucFracFbDiv; int ucPostDiv; int ucPpll; int ucCRTC; int ucRefDivSrc; void* usFbDiv; void* usRefDiv; void* usPixelClock; } ;
union set_pixel_clock {TYPE_6__ v6; TYPE_5__ v5; TYPE_4__ v3; TYPE_3__ v2; TYPE_2__ v1; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct radeon_atom_ss {int type; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int ATOM_CRTC2 ; 
 int ATOM_DISABLE ; 
 int ATOM_ENCODER_MODE_HDMI ; 
 int ATOM_EXTERNAL_SS_MASK ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIXEL_CLOCK_MISC_CRTC_SEL_CRTC1 ; 
 int /*<<< orphan*/  PIXEL_CLOCK_MISC_CRTC_SEL_CRTC2 ; 
 int /*<<< orphan*/  PIXEL_CLOCK_MISC_REF_DIV_SRC ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V5_MISC_HDMI_24BPP ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V5_MISC_HDMI_30BPP ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V5_MISC_HDMI_32BPP ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V5_MISC_REF_DIV_SRC ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V6_MISC_HDMI_24BPP ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V6_MISC_HDMI_30BPP_V6 ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V6_MISC_HDMI_36BPP_V6 ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V6_MISC_HDMI_48BPP ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V6_MISC_REF_DIV_SRC ; 
 int /*<<< orphan*/  SetPixelClock ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (union set_pixel_clock*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void atombios_crtc_program_pll(struct drm_crtc *crtc,
				      u32 crtc_id,
				      int pll_id,
				      u32 encoder_mode,
				      u32 encoder_id,
				      u32 clock,
				      u32 ref_div,
				      u32 fb_div,
				      u32 frac_fb_div,
				      u32 post_div,
				      int bpc,
				      bool ss_enabled,
				      struct radeon_atom_ss *ss)
{
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	u8 frev, crev;
	int index = GetIndexIntoMasterTable(COMMAND, SetPixelClock);
	union set_pixel_clock args;

	memset(&args, 0, sizeof(args));

	if (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev,
				   &crev))
		return;

	switch (frev) {
	case 1:
		switch (crev) {
		case 1:
			if (clock == ATOM_DISABLE)
				return;
			args.v1.usPixelClock = cpu_to_le16(clock / 10);
			args.v1.usRefDiv = cpu_to_le16(ref_div);
			args.v1.usFbDiv = cpu_to_le16(fb_div);
			args.v1.ucFracFbDiv = frac_fb_div;
			args.v1.ucPostDiv = post_div;
			args.v1.ucPpll = pll_id;
			args.v1.ucCRTC = crtc_id;
			args.v1.ucRefDivSrc = 1;
			break;
		case 2:
			args.v2.usPixelClock = cpu_to_le16(clock / 10);
			args.v2.usRefDiv = cpu_to_le16(ref_div);
			args.v2.usFbDiv = cpu_to_le16(fb_div);
			args.v2.ucFracFbDiv = frac_fb_div;
			args.v2.ucPostDiv = post_div;
			args.v2.ucPpll = pll_id;
			args.v2.ucCRTC = crtc_id;
			args.v2.ucRefDivSrc = 1;
			break;
		case 3:
			args.v3.usPixelClock = cpu_to_le16(clock / 10);
			args.v3.usRefDiv = cpu_to_le16(ref_div);
			args.v3.usFbDiv = cpu_to_le16(fb_div);
			args.v3.ucFracFbDiv = frac_fb_div;
			args.v3.ucPostDiv = post_div;
			args.v3.ucPpll = pll_id;
			if (crtc_id == ATOM_CRTC2)
				args.v3.ucMiscInfo = PIXEL_CLOCK_MISC_CRTC_SEL_CRTC2;
			else
				args.v3.ucMiscInfo = PIXEL_CLOCK_MISC_CRTC_SEL_CRTC1;
			if (ss_enabled && (ss->type & ATOM_EXTERNAL_SS_MASK))
				args.v3.ucMiscInfo |= PIXEL_CLOCK_MISC_REF_DIV_SRC;
			args.v3.ucTransmitterId = encoder_id;
			args.v3.ucEncoderMode = encoder_mode;
			break;
		case 5:
			args.v5.ucCRTC = crtc_id;
			args.v5.usPixelClock = cpu_to_le16(clock / 10);
			args.v5.ucRefDiv = ref_div;
			args.v5.usFbDiv = cpu_to_le16(fb_div);
			args.v5.ulFbDivDecFrac = cpu_to_le32(frac_fb_div * 100000);
			args.v5.ucPostDiv = post_div;
			args.v5.ucMiscInfo = 0; /* HDMI depth, etc. */
			if (ss_enabled && (ss->type & ATOM_EXTERNAL_SS_MASK))
				args.v5.ucMiscInfo |= PIXEL_CLOCK_V5_MISC_REF_DIV_SRC;
			if (encoder_mode == ATOM_ENCODER_MODE_HDMI) {
				switch (bpc) {
				case 8:
				default:
					args.v5.ucMiscInfo |= PIXEL_CLOCK_V5_MISC_HDMI_24BPP;
					break;
				case 10:
					/* yes this is correct, the atom define is wrong */
					args.v5.ucMiscInfo |= PIXEL_CLOCK_V5_MISC_HDMI_32BPP;
					break;
				case 12:
					/* yes this is correct, the atom define is wrong */
					args.v5.ucMiscInfo |= PIXEL_CLOCK_V5_MISC_HDMI_30BPP;
					break;
				}
			}
			args.v5.ucTransmitterID = encoder_id;
			args.v5.ucEncoderMode = encoder_mode;
			args.v5.ucPpll = pll_id;
			break;
		case 6:
			args.v6.ulDispEngClkFreq = cpu_to_le32(crtc_id << 24 | clock / 10);
			args.v6.ucRefDiv = ref_div;
			args.v6.usFbDiv = cpu_to_le16(fb_div);
			args.v6.ulFbDivDecFrac = cpu_to_le32(frac_fb_div * 100000);
			args.v6.ucPostDiv = post_div;
			args.v6.ucMiscInfo = 0; /* HDMI depth, etc. */
			if (ss_enabled && (ss->type & ATOM_EXTERNAL_SS_MASK))
				args.v6.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_REF_DIV_SRC;
			if (encoder_mode == ATOM_ENCODER_MODE_HDMI) {
				switch (bpc) {
				case 8:
				default:
					args.v6.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_HDMI_24BPP;
					break;
				case 10:
					args.v6.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_HDMI_30BPP_V6;
					break;
				case 12:
					args.v6.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_HDMI_36BPP_V6;
					break;
				case 16:
					args.v6.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_HDMI_48BPP;
					break;
				}
			}
			args.v6.ucTransmitterID = encoder_id;
			args.v6.ucEncoderMode = encoder_mode;
			args.v6.ucPpll = pll_id;
			break;
		default:
			DRM_ERROR("Unknown table version %d %d\n", frev, crev);
			return;
		}
		break;
	default:
		DRM_ERROR("Unknown table version %d %d\n", frev, crev);
		return;
	}

	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);
}