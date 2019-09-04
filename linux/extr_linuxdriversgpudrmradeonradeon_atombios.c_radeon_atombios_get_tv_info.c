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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct radeon_mode_info {TYPE_1__* atom_context; } ;
struct radeon_device {struct radeon_mode_info mode_info; } ;
struct _ATOM_ANALOG_TV_INFO {int ucTV_BootUpDefaultStandard; } ;
typedef  enum radeon_tv_std { ____Placeholder_radeon_tv_std } radeon_tv_std ;
struct TYPE_2__ {scalar_t__ bios; } ;

/* Variables and functions */
#define  ATOM_TV_NTSC 135 
#define  ATOM_TV_NTSCJ 134 
#define  ATOM_TV_PAL 133 
#define  ATOM_TV_PAL60 132 
#define  ATOM_TV_PALCN 131 
#define  ATOM_TV_PALM 130 
#define  ATOM_TV_PALN 129 
#define  ATOM_TV_SECAM 128 
 int /*<<< orphan*/  AnalogTV_Info ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TV_STD_NTSC ; 
 int TV_STD_NTSC_J ; 
 int TV_STD_PAL ; 
 int TV_STD_PAL_60 ; 
 int TV_STD_PAL_CN ; 
 int TV_STD_PAL_M ; 
 int TV_STD_PAL_N ; 
 int TV_STD_SECAM ; 
 scalar_t__ atom_parse_data_header (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 

enum radeon_tv_std
radeon_atombios_get_tv_info(struct radeon_device *rdev)
{
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, AnalogTV_Info);
	uint16_t data_offset;
	uint8_t frev, crev;
	struct _ATOM_ANALOG_TV_INFO *tv_info;
	enum radeon_tv_std tv_std = TV_STD_NTSC;

	if (atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {

		tv_info = (struct _ATOM_ANALOG_TV_INFO *)
			(mode_info->atom_context->bios + data_offset);

		switch (tv_info->ucTV_BootUpDefaultStandard) {
		case ATOM_TV_NTSC:
			tv_std = TV_STD_NTSC;
			DRM_DEBUG_KMS("Default TV standard: NTSC\n");
			break;
		case ATOM_TV_NTSCJ:
			tv_std = TV_STD_NTSC_J;
			DRM_DEBUG_KMS("Default TV standard: NTSC-J\n");
			break;
		case ATOM_TV_PAL:
			tv_std = TV_STD_PAL;
			DRM_DEBUG_KMS("Default TV standard: PAL\n");
			break;
		case ATOM_TV_PALM:
			tv_std = TV_STD_PAL_M;
			DRM_DEBUG_KMS("Default TV standard: PAL-M\n");
			break;
		case ATOM_TV_PALN:
			tv_std = TV_STD_PAL_N;
			DRM_DEBUG_KMS("Default TV standard: PAL-N\n");
			break;
		case ATOM_TV_PALCN:
			tv_std = TV_STD_PAL_CN;
			DRM_DEBUG_KMS("Default TV standard: PAL-CN\n");
			break;
		case ATOM_TV_PAL60:
			tv_std = TV_STD_PAL_60;
			DRM_DEBUG_KMS("Default TV standard: PAL-60\n");
			break;
		case ATOM_TV_SECAM:
			tv_std = TV_STD_SECAM;
			DRM_DEBUG_KMS("Default TV standard: SECAM\n");
			break;
		default:
			tv_std = TV_STD_NTSC;
			DRM_DEBUG_KMS("Unknown TV standard; defaulting to NTSC\n");
			break;
		}
	}
	return tv_std;
}