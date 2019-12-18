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
struct dc_bios {int dummy; } ;
struct bios_parser {int dummy; } ;
struct atom_data_revision {int major; int /*<<< orphan*/  minor; } ;
typedef  enum as_signal_type { ____Placeholder_as_signal_type } as_signal_type ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_InternalSS_Info ; 
 int ATOM_COMMON_TABLE_HEADER ; 
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int /*<<< orphan*/  DATA_TABLES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_IMAGE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_atom_data_table_revision (int,struct atom_data_revision*) ; 
 int /*<<< orphan*/  get_ss_entry_number (struct bios_parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ss_entry_number_from_internal_ss_info_tbl_V3_1 (struct bios_parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ss_entry_number_from_ss_info_tbl (struct bios_parser*,int /*<<< orphan*/ ) ; 
 int header ; 
 int /*<<< orphan*/  signal_to_ss_id (int) ; 

__attribute__((used)) static uint32_t bios_parser_get_ss_entry_number(
	struct dc_bios *dcb,
	enum as_signal_type signal)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);
	uint32_t ss_id = 0;
	ATOM_COMMON_TABLE_HEADER *header;
	struct atom_data_revision revision;

	ss_id = signal_to_ss_id(signal);

	if (!DATA_TABLES(ASIC_InternalSS_Info))
		return get_ss_entry_number_from_ss_info_tbl(bp, ss_id);

	header = GET_IMAGE(ATOM_COMMON_TABLE_HEADER,
			DATA_TABLES(ASIC_InternalSS_Info));
	get_atom_data_table_revision(header, &revision);

	switch (revision.major) {
	case 2:
		switch (revision.minor) {
		case 1:
			return get_ss_entry_number(bp, ss_id);
		default:
			break;
		}
		break;
	case 3:
		switch (revision.minor) {
		case 1:
			return
				get_ss_entry_number_from_internal_ss_info_tbl_V3_1(
						bp, ss_id);
		default:
			break;
		}
		break;
	default:
		break;
	}

	return 0;
}