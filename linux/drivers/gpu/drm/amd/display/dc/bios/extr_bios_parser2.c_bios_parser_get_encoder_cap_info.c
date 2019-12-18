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
struct graphics_object_id {int dummy; } ;
struct dc_bios {int dummy; } ;
struct bp_encoder_cap_info {int DP_HBR2_CAP; int DP_HBR2_EN; int DP_HBR3_EN; int HDMI_6GB_EN; int DP_IS_USB_C; } ;
struct bios_parser {int dummy; } ;
struct atom_encoder_caps_record {int encodercaps; } ;
struct atom_display_object_path_v2 {int dummy; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;

/* Variables and functions */
 int ATOM_ENCODER_CAP_RECORD_HBR2 ; 
 int ATOM_ENCODER_CAP_RECORD_HBR2_EN ; 
 int ATOM_ENCODER_CAP_RECORD_HBR3_EN ; 
 int ATOM_ENCODER_CAP_RECORD_HDMI6Gbps_EN ; 
 int ATOM_ENCODER_CAP_RECORD_USB_C_TYPE ; 
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int BP_RESULT_BADINPUT ; 
 int BP_RESULT_NORECORD ; 
 int BP_RESULT_OK ; 
 struct atom_display_object_path_v2* get_bios_object (struct bios_parser*,struct graphics_object_id) ; 
 struct atom_encoder_caps_record* get_encoder_cap_record (struct bios_parser*,struct atom_display_object_path_v2*) ; 

__attribute__((used)) static enum bp_result bios_parser_get_encoder_cap_info(
	struct dc_bios *dcb,
	struct graphics_object_id object_id,
	struct bp_encoder_cap_info *info)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	struct atom_display_object_path_v2 *object;
	struct atom_encoder_caps_record *record = NULL;

	if (!info)
		return BP_RESULT_BADINPUT;

	object = get_bios_object(bp, object_id);

	if (!object)
		return BP_RESULT_BADINPUT;

	record = get_encoder_cap_record(bp, object);
	if (!record)
		return BP_RESULT_NORECORD;

	info->DP_HBR2_CAP = (record->encodercaps &
			ATOM_ENCODER_CAP_RECORD_HBR2) ? 1 : 0;
	info->DP_HBR2_EN = (record->encodercaps &
			ATOM_ENCODER_CAP_RECORD_HBR2_EN) ? 1 : 0;
	info->DP_HBR3_EN = (record->encodercaps &
			ATOM_ENCODER_CAP_RECORD_HBR3_EN) ? 1 : 0;
	info->HDMI_6GB_EN = (record->encodercaps &
			ATOM_ENCODER_CAP_RECORD_HDMI6Gbps_EN) ? 1 : 0;
	info->DP_IS_USB_C = (record->encodercaps &
			ATOM_ENCODER_CAP_RECORD_USB_C_TYPE) ? 1 : 0;

	return BP_RESULT_OK;
}