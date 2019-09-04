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
struct TYPE_9__ {int ChannelNumber; int /*<<< orphan*/  DiscReason; int /*<<< orphan*/  RemoteResyncs; int /*<<< orphan*/  LocalResyncs; int /*<<< orphan*/  RemoteRetrains; int /*<<< orphan*/  LocalRetrains; int /*<<< orphan*/  MAE; int /*<<< orphan*/  SNRdb; int /*<<< orphan*/  EchoLeveldBm; int /*<<< orphan*/  RxLeveldBm; int /*<<< orphan*/  SymbolRate; int /*<<< orphan*/  RoundtripMsec; int /*<<< orphan*/  RxSpeed; int /*<<< orphan*/  TxSpeed; int /*<<< orphan*/  Options; int /*<<< orphan*/  Norm; int /*<<< orphan*/  Event; } ;
typedef  TYPE_3__ diva_trace_modem_state_t ;
struct TYPE_10__ {scalar_t__ cur_parse_entry; scalar_t__ parse_entries; scalar_t__* modem_parse_entry_first; size_t* modem_parse_entry_last; TYPE_2__* parse_table; TYPE_1__* lines; } ;
typedef  TYPE_4__ diva_strace_context_t ;
struct TYPE_8__ {int /*<<< orphan*/ * variable; int /*<<< orphan*/  path; } ;
struct TYPE_7__ {TYPE_3__ modem; } ;

/* Variables and functions */
 scalar_t__ MODEM_PARSE_ENTRIES ; 
 int /*<<< orphan*/  diva_trace_error (TYPE_4__*,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void diva_create_modem_parse_table(diva_strace_context_t *pLib,
					  int Channel) {
	diva_trace_modem_state_t *pModem = &pLib->lines[Channel].modem;
	int nr = Channel + 1;

	if ((pLib->cur_parse_entry + MODEM_PARSE_ENTRIES) >= pLib->parse_entries) {
		diva_trace_error(pLib, -1, __FILE__, __LINE__);
		return;
	}
	pModem->ChannelNumber = nr;

	pLib->modem_parse_entry_first[Channel] = pLib->cur_parse_entry;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\Event", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->Event;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\Norm", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->Norm;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\Options", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->Options;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\TX Speed", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->TxSpeed;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\RX Speed", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->RxSpeed;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\Roundtrip ms", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->RoundtripMsec;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\Symbol Rate", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->SymbolRate;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\RX Level dBm", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->RxLeveldBm;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\Echo Level dBm", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->EchoLeveldBm;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\SNR dB", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->SNRdb;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\MAE", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->MAE;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\Local Retrains", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->LocalRetrains;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\Remote Retrains", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->RemoteRetrains;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\Local Resyncs", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->LocalResyncs;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\Remote Resyncs", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->RemoteResyncs;

	sprintf(pLib->parse_table[pLib->cur_parse_entry].path,
		"State\\B%d\\Modem\\Disc Reason", nr);
	pLib->parse_table[pLib->cur_parse_entry++].variable = &pModem->DiscReason;

	pLib->modem_parse_entry_last[Channel] = pLib->cur_parse_entry - 1;
}