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
typedef  scalar_t__ uint32_t ;
struct spread_spectrum_info {int dummy; } ;
struct bios_parser {int dummy; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;

/* Variables and functions */
 scalar_t__ ASIC_INTERNAL_SS_ON_DP ; 
 scalar_t__ ASIC_INTERNAL_SS_ON_LVDS ; 
 int BP_RESULT_BADINPUT ; 
 int get_ss_info_from_internal_ss_info_tbl_V2_1 (struct bios_parser*,scalar_t__,struct spread_spectrum_info*) ; 
 int get_ss_info_from_ss_info_table (struct bios_parser*,scalar_t__,struct spread_spectrum_info*) ; 

__attribute__((used)) static enum bp_result get_ss_info_from_tbl(
	struct bios_parser *bp,
	uint32_t id,
	struct spread_spectrum_info *ss_info)
{
	if (!ss_info) /* check for bad input, if ss_info is not NULL */
		return BP_RESULT_BADINPUT;
	/* for SS_Info table only support DP and LVDS */
	if (id == ASIC_INTERNAL_SS_ON_DP || id == ASIC_INTERNAL_SS_ON_LVDS)
		return get_ss_info_from_ss_info_table(bp, id, ss_info);
	else
		return get_ss_info_from_internal_ss_info_tbl_V2_1(bp, id,
			ss_info);
}