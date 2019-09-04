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
typedef  int /*<<< orphan*/  uint32_t ;
struct spread_spectrum_info {int dummy; } ;
struct dc_bios {int dummy; } ;
struct bios_parser {int dummy; } ;
struct atom_data_revision {int major; int /*<<< orphan*/  minor; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
typedef  enum as_signal_type { ____Placeholder_as_signal_type } as_signal_type ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_InternalSS_Info ; 
 int ATOM_COMMON_TABLE_HEADER ; 
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int BP_RESULT_BADINPUT ; 
 int BP_RESULT_UNSUPPORTED ; 
 int /*<<< orphan*/  DATA_TABLES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_IMAGE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_atom_data_table_revision (int,struct atom_data_revision*) ; 
 int get_ss_info_from_ss_info_table (struct bios_parser*,int /*<<< orphan*/ ,struct spread_spectrum_info*) ; 
 int get_ss_info_from_tbl (struct bios_parser*,int /*<<< orphan*/ ,struct spread_spectrum_info*) ; 
 int get_ss_info_v3_1 (struct bios_parser*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spread_spectrum_info*) ; 
 int header ; 
 int /*<<< orphan*/  signal_to_ss_id (int) ; 

__attribute__((used)) static enum bp_result bios_parser_get_spread_spectrum_info(
	struct dc_bios *dcb,
	enum as_signal_type signal,
	uint32_t index,
	struct spread_spectrum_info *ss_info)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	enum bp_result result = BP_RESULT_UNSUPPORTED;
	uint32_t clk_id_ss = 0;
	ATOM_COMMON_TABLE_HEADER *header;
	struct atom_data_revision tbl_revision;

	if (!ss_info) /* check for bad input */
		return BP_RESULT_BADINPUT;
	/* signal translation */
	clk_id_ss = signal_to_ss_id(signal);

	if (!DATA_TABLES(ASIC_InternalSS_Info))
		if (!index)
			return get_ss_info_from_ss_info_table(bp, clk_id_ss,
				ss_info);

	header = GET_IMAGE(ATOM_COMMON_TABLE_HEADER,
		DATA_TABLES(ASIC_InternalSS_Info));
	get_atom_data_table_revision(header, &tbl_revision);

	switch (tbl_revision.major) {
	case 2:
		switch (tbl_revision.minor) {
		case 1:
			/* there can not be more then one entry for Internal
			 * SS Info table version 2.1 */
			if (!index)
				return get_ss_info_from_tbl(bp, clk_id_ss,
						ss_info);
			break;
		default:
			break;
		}
		break;

	case 3:
		switch (tbl_revision.minor) {
		case 1:
			return get_ss_info_v3_1(bp, clk_id_ss, index, ss_info);
		default:
			break;
		}
		break;
	default:
		break;
	}
	/* there can not be more then one entry for SS Info table */
	return result;
}