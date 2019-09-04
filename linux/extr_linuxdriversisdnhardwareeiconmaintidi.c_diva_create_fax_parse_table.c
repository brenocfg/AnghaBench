#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ChannelNumber; int /*<<< orphan*/  Disc_Reason; int /*<<< orphan*/  Scanline_Time; int /*<<< orphan*/  Paper_Length; int /*<<< orphan*/  Paper_Width; int /*<<< orphan*/  Resolution; int /*<<< orphan*/  Speed; int /*<<< orphan*/ * Password; int /*<<< orphan*/ * Subaddress; int /*<<< orphan*/ * Station_ID; int /*<<< orphan*/  Features; int /*<<< orphan*/  Page_Counter; int /*<<< orphan*/  Event; } ;
typedef  TYPE_3__ diva_trace_fax_state_t ;
struct TYPE_10__ {scalar_t__ cur_parse_entry; scalar_t__ parse_entries; scalar_t__* fax_parse_entry_first; size_t* fax_parse_entry_last; TYPE_2__* parse_table; TYPE_1__* lines; } ;
typedef  TYPE_4__ diva_strace_context_t ;
struct TYPE_8__ {int /*<<< orphan*/ * variable; int /*<<< orphan*/  path; } ;
struct TYPE_7__ {TYPE_3__ fax; } ;

/* Variables and functions */
 scalar_t__ FAX_PARSE_ENTRIES ; 
 int /*<<< orphan*/  diva_trace_error (TYPE_4__*,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void diva_create_fax_parse_table(diva_strace_context_t *pLib,
					int Channel) {
	diva_trace_fax_state_t *pFax = &pLib->lines[Channel].fax;
	int nr = Channel + 1;

	if ((pLib->cur_parse_entry + FAX_PARSE_ENTRIES) >= pLib->parse_entries) {
		diva_trace_error(pLib, -1, __FILE__, __LINE__);
		return;
	}
	pFax->ChannelNumber = nr;

	pLib->fax_parse_entry_first[Channel] = pLib->cur_parse_entry;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\FAX\\Event", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pFax->Event;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\FAX\\Page Counter", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pFax->Page_Counter;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\FAX\\Features", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pFax->Features;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\FAX\\Station ID", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pFax->Station_ID[0];

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\FAX\\Subaddress", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pFax->Subaddress[0];

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\FAX\\Password", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pFax->Password[0];

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\FAX\\Speed", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pFax->Speed;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\FAX\\Resolution", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pFax->Resolution;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\FAX\\Paper Width", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pFax->Paper_Width;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\FAX\\Paper Length", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pFax->Paper_Length;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\FAX\\Scanline Time", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pFax->Scanline_Time;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\FAX\\Disc Reason", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pFax->Disc_Reason;

	pLib->fax_parse_entry_last[Channel] = pLib->cur_parse_entry - 1;
}