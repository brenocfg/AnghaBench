#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ChannelNumber; int /*<<< orphan*/ * UserID; int /*<<< orphan*/  LastDisconnecCause; int /*<<< orphan*/  CallReference; int /*<<< orphan*/  Charges; int /*<<< orphan*/  call_LLC; int /*<<< orphan*/  call_HLC; int /*<<< orphan*/  call_BC; int /*<<< orphan*/ * LocalSubAddress; int /*<<< orphan*/ * LocalAddress; int /*<<< orphan*/ * RemoteSubAddress; int /*<<< orphan*/ * RemoteAddress; int /*<<< orphan*/ * Layer3; int /*<<< orphan*/ * Layer2; int /*<<< orphan*/ * Line; int /*<<< orphan*/ * Framing; } ;
typedef  TYPE_2__ diva_trace_line_state_t ;
struct TYPE_8__ {scalar_t__ cur_parse_entry; scalar_t__ parse_entries; scalar_t__* line_parse_entry_first; size_t* line_parse_entry_last; TYPE_1__* parse_table; TYPE_2__* lines; } ;
typedef  TYPE_3__ diva_strace_context_t ;
struct TYPE_6__ {int /*<<< orphan*/ * variable; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 scalar_t__ LINE_PARSE_ENTRIES ; 
 int /*<<< orphan*/  diva_trace_error (TYPE_3__*,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void diva_create_line_parse_table(diva_strace_context_t *pLib,
					 int Channel) {
	diva_trace_line_state_t *pLine = &pLib->lines[Channel];
	int nr = Channel + 1;

	if ((pLib->cur_parse_entry + LINE_PARSE_ENTRIES) >= pLib->parse_entries) {
		diva_trace_error(pLib, -1, __FILE__, __LINE__);
		return;
	}

	pLine->ChannelNumber = nr;

	pLib->line_parse_entry_first[Channel] = pLib->cur_parse_entry;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Framing", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pLine->Framing[0];

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Line", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pLine->Line[0];

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Layer2", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pLine->Layer2[0];

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Layer3", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pLine->Layer3[0];

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Remote Address", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLine->RemoteAddress[0];

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Remote SubAddr", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLine->RemoteSubAddress[0];

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Local Address", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLine->LocalAddress[0];

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Local SubAddr", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLine->LocalSubAddress[0];

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\BC", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pLine->call_BC;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\HLC", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pLine->call_HLC;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\LLC", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pLine->call_LLC;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Charges", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pLine->Charges;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Call Reference", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pLine->CallReference;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Last Disc Cause", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLine->LastDisconnecCause;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\User ID", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pLine->UserID[0];

	pLib->line_parse_entry_last[Channel] = pLib->cur_parse_entry - 1;
}