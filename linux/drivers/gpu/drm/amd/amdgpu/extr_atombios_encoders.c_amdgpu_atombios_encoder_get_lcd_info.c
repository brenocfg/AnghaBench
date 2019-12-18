#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  usAccess; } ;
struct TYPE_11__ {int /*<<< orphan*/  usImageVSize; int /*<<< orphan*/  usImageHSize; TYPE_2__ susModeMiscInfo; int /*<<< orphan*/  usVSyncWidth; int /*<<< orphan*/  usVSyncOffset; int /*<<< orphan*/  usVBlanking_Time; int /*<<< orphan*/  usHSyncWidth; int /*<<< orphan*/  usHSyncOffset; int /*<<< orphan*/  usHBlanking_Time; int /*<<< orphan*/  usVActive; int /*<<< orphan*/  usHActive; int /*<<< orphan*/  usPixClk; } ;
struct TYPE_12__ {int /*<<< orphan*/  usModePatchTableOffset; int /*<<< orphan*/  ucSS_Id; TYPE_3__ sLCDTiming; int /*<<< orphan*/  ucLVDS_Misc; int /*<<< orphan*/  usOffDelayInMs; } ;
union lvds_info {TYPE_4__ info; } ;
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int u8 ;
struct edid {int dummy; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct amdgpu_mode_info {int bios_hardcoded_edid_size; struct edid* bios_hardcoded_edid; TYPE_8__* atom_context; } ;
struct TYPE_15__ {int clock; int hdisplay; int vdisplay; int htotal; int hsync_start; int hsync_end; int vtotal; int vsync_start; int vsync_end; int width_mm; int height_mm; int /*<<< orphan*/  flags; } ;
struct amdgpu_encoder_atom_dig {int panel_pwr_delay; int linkb; TYPE_7__ native_mode; int /*<<< orphan*/  lcd_ss_id; int /*<<< orphan*/  lcd_misc; } ;
struct TYPE_9__ {struct drm_device* dev; } ;
struct amdgpu_encoder {int encoder_enum; TYPE_7__ native_mode; TYPE_1__ base; } ;
struct amdgpu_device {struct amdgpu_mode_info mode_info; } ;
struct TYPE_16__ {int bios; } ;
struct TYPE_14__ {scalar_t__ ucFakeEDIDLength; int /*<<< orphan*/ * ucFakeEDIDString; } ;
struct TYPE_13__ {int usHSize; int usVSize; } ;
typedef  int /*<<< orphan*/  ATOM_PATCH_RECORD_MODE ;
typedef  TYPE_5__ ATOM_PANEL_RESOLUTION_PATCH_RECORD ;
typedef  int /*<<< orphan*/  ATOM_LCD_RTS_RECORD ;
typedef  int /*<<< orphan*/  ATOM_LCD_MODE_CONTROL_CAP ;
typedef  TYPE_6__ ATOM_FAKE_EDID_PATCH_RECORD ;

/* Variables and functions */
 int ATOM_COMPOSITESYNC ; 
 int ATOM_DOUBLE_CLOCK_MODE ; 
 int ATOM_HSYNC_POLARITY ; 
 int ATOM_INTERLACE ; 
 int ATOM_RECORD_END_TYPE ; 
 int ATOM_VSYNC_POLARITY ; 
 int /*<<< orphan*/  CRTC_INTERLACE_HALVE_V ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_CSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_DBLSCAN ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_NHSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_NVSYNC ; 
 scalar_t__ EDID_LENGTH ; 
 int ENUM_ID_MASK ; 
 int ENUM_ID_SHIFT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  LCD_CAP_RECORD_TYPE 132 
#define  LCD_FAKE_EDID_PATCH_RECORD_TYPE 131 
#define  LCD_MODE_PATCH_RECORD_MODE_TYPE 130 
#define  LCD_PANEL_RESOLUTION_RECORD_TYPE 129 
#define  LCD_RTS_RECORD_TYPE 128 
 int /*<<< orphan*/  LVDS_Info ; 
 scalar_t__ amdgpu_atom_parse_data_header (TYPE_8__*,int,int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/  drm_edid_is_valid (struct edid*) ; 
 int /*<<< orphan*/  drm_mode_set_crtcinfo (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 struct edid* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct amdgpu_encoder_atom_dig* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,scalar_t__) ; 

struct amdgpu_encoder_atom_dig *
amdgpu_atombios_encoder_get_lcd_info(struct amdgpu_encoder *encoder)
{
	struct drm_device *dev = encoder->base.dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, LVDS_Info);
	uint16_t data_offset, misc;
	union lvds_info *lvds_info;
	uint8_t frev, crev;
	struct amdgpu_encoder_atom_dig *lvds = NULL;
	int encoder_enum = (encoder->encoder_enum & ENUM_ID_MASK) >> ENUM_ID_SHIFT;

	if (amdgpu_atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {
		lvds_info =
			(union lvds_info *)(mode_info->atom_context->bios + data_offset);
		lvds =
		    kzalloc(sizeof(struct amdgpu_encoder_atom_dig), GFP_KERNEL);

		if (!lvds)
			return NULL;

		lvds->native_mode.clock =
		    le16_to_cpu(lvds_info->info.sLCDTiming.usPixClk) * 10;
		lvds->native_mode.hdisplay =
		    le16_to_cpu(lvds_info->info.sLCDTiming.usHActive);
		lvds->native_mode.vdisplay =
		    le16_to_cpu(lvds_info->info.sLCDTiming.usVActive);
		lvds->native_mode.htotal = lvds->native_mode.hdisplay +
			le16_to_cpu(lvds_info->info.sLCDTiming.usHBlanking_Time);
		lvds->native_mode.hsync_start = lvds->native_mode.hdisplay +
			le16_to_cpu(lvds_info->info.sLCDTiming.usHSyncOffset);
		lvds->native_mode.hsync_end = lvds->native_mode.hsync_start +
			le16_to_cpu(lvds_info->info.sLCDTiming.usHSyncWidth);
		lvds->native_mode.vtotal = lvds->native_mode.vdisplay +
			le16_to_cpu(lvds_info->info.sLCDTiming.usVBlanking_Time);
		lvds->native_mode.vsync_start = lvds->native_mode.vdisplay +
			le16_to_cpu(lvds_info->info.sLCDTiming.usVSyncOffset);
		lvds->native_mode.vsync_end = lvds->native_mode.vsync_start +
			le16_to_cpu(lvds_info->info.sLCDTiming.usVSyncWidth);
		lvds->panel_pwr_delay =
		    le16_to_cpu(lvds_info->info.usOffDelayInMs);
		lvds->lcd_misc = lvds_info->info.ucLVDS_Misc;

		misc = le16_to_cpu(lvds_info->info.sLCDTiming.susModeMiscInfo.usAccess);
		if (misc & ATOM_VSYNC_POLARITY)
			lvds->native_mode.flags |= DRM_MODE_FLAG_NVSYNC;
		if (misc & ATOM_HSYNC_POLARITY)
			lvds->native_mode.flags |= DRM_MODE_FLAG_NHSYNC;
		if (misc & ATOM_COMPOSITESYNC)
			lvds->native_mode.flags |= DRM_MODE_FLAG_CSYNC;
		if (misc & ATOM_INTERLACE)
			lvds->native_mode.flags |= DRM_MODE_FLAG_INTERLACE;
		if (misc & ATOM_DOUBLE_CLOCK_MODE)
			lvds->native_mode.flags |= DRM_MODE_FLAG_DBLSCAN;

		lvds->native_mode.width_mm = le16_to_cpu(lvds_info->info.sLCDTiming.usImageHSize);
		lvds->native_mode.height_mm = le16_to_cpu(lvds_info->info.sLCDTiming.usImageVSize);

		/* set crtc values */
		drm_mode_set_crtcinfo(&lvds->native_mode, CRTC_INTERLACE_HALVE_V);

		lvds->lcd_ss_id = lvds_info->info.ucSS_Id;

		encoder->native_mode = lvds->native_mode;

		if (encoder_enum == 2)
			lvds->linkb = true;
		else
			lvds->linkb = false;

		/* parse the lcd record table */
		if (le16_to_cpu(lvds_info->info.usModePatchTableOffset)) {
			ATOM_FAKE_EDID_PATCH_RECORD *fake_edid_record;
			ATOM_PANEL_RESOLUTION_PATCH_RECORD *panel_res_record;
			bool bad_record = false;
			u8 *record;

			if ((frev == 1) && (crev < 2))
				/* absolute */
				record = (u8 *)(mode_info->atom_context->bios +
						le16_to_cpu(lvds_info->info.usModePatchTableOffset));
			else
				/* relative */
				record = (u8 *)(mode_info->atom_context->bios +
						data_offset +
						le16_to_cpu(lvds_info->info.usModePatchTableOffset));
			while (*record != ATOM_RECORD_END_TYPE) {
				switch (*record) {
				case LCD_MODE_PATCH_RECORD_MODE_TYPE:
					record += sizeof(ATOM_PATCH_RECORD_MODE);
					break;
				case LCD_RTS_RECORD_TYPE:
					record += sizeof(ATOM_LCD_RTS_RECORD);
					break;
				case LCD_CAP_RECORD_TYPE:
					record += sizeof(ATOM_LCD_MODE_CONTROL_CAP);
					break;
				case LCD_FAKE_EDID_PATCH_RECORD_TYPE:
					fake_edid_record = (ATOM_FAKE_EDID_PATCH_RECORD *)record;
					if (fake_edid_record->ucFakeEDIDLength) {
						struct edid *edid;
						int edid_size =
							max((int)EDID_LENGTH, (int)fake_edid_record->ucFakeEDIDLength);
						edid = kmalloc(edid_size, GFP_KERNEL);
						if (edid) {
							memcpy((u8 *)edid, (u8 *)&fake_edid_record->ucFakeEDIDString[0],
							       fake_edid_record->ucFakeEDIDLength);

							if (drm_edid_is_valid(edid)) {
								adev->mode_info.bios_hardcoded_edid = edid;
								adev->mode_info.bios_hardcoded_edid_size = edid_size;
							} else
								kfree(edid);
						}
					}
					record += fake_edid_record->ucFakeEDIDLength ?
						fake_edid_record->ucFakeEDIDLength + 2 :
						sizeof(ATOM_FAKE_EDID_PATCH_RECORD);
					break;
				case LCD_PANEL_RESOLUTION_RECORD_TYPE:
					panel_res_record = (ATOM_PANEL_RESOLUTION_PATCH_RECORD *)record;
					lvds->native_mode.width_mm = panel_res_record->usHSize;
					lvds->native_mode.height_mm = panel_res_record->usVSize;
					record += sizeof(ATOM_PANEL_RESOLUTION_PATCH_RECORD);
					break;
				default:
					DRM_ERROR("Bad LCD record %d\n", *record);
					bad_record = true;
					break;
				}
				if (bad_record)
					break;
			}
		}
	}
	return lvds;
}