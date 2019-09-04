#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct graphics_object_id {int dummy; } ;
struct dc_bios {int dummy; } ;
struct bp_encoder_cap_info {int /*<<< orphan*/  HDMI_6GB_EN; int /*<<< orphan*/  DP_HBR3_EN; int /*<<< orphan*/  DP_HBR2_EN; } ;
struct bios_parser {int dummy; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_3__ {int /*<<< orphan*/  usHDMI6GEn; int /*<<< orphan*/  usHBR3En; int /*<<< orphan*/  usHBR2En; } ;
typedef  int /*<<< orphan*/  ATOM_OBJECT ;
typedef  TYPE_1__ ATOM_ENCODER_CAP_RECORD_V2 ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int BP_RESULT_BADINPUT ; 
 int BP_RESULT_NORECORD ; 
 int BP_RESULT_OK ; 
 int /*<<< orphan*/ * get_bios_object (struct bios_parser*,struct graphics_object_id) ; 
 TYPE_1__* get_encoder_cap_record (struct bios_parser*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum bp_result bios_parser_get_encoder_cap_info(
	struct dc_bios *dcb,
	struct graphics_object_id object_id,
	struct bp_encoder_cap_info *info)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	ATOM_OBJECT *object;
	ATOM_ENCODER_CAP_RECORD_V2 *record = NULL;

	if (!info)
		return BP_RESULT_BADINPUT;

	object = get_bios_object(bp, object_id);

	if (!object)
		return BP_RESULT_BADINPUT;

	record = get_encoder_cap_record(bp, object);
	if (!record)
		return BP_RESULT_NORECORD;

	info->DP_HBR2_EN = record->usHBR2En;
	info->DP_HBR3_EN = record->usHBR3En;
	info->HDMI_6GB_EN = record->usHDMI6GEn;
	return BP_RESULT_OK;
}