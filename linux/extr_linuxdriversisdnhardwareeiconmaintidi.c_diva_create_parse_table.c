#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  R_Errors; int /*<<< orphan*/  R_Bytes; int /*<<< orphan*/  R_Frames; int /*<<< orphan*/  X_Errors; int /*<<< orphan*/  X_Bytes; int /*<<< orphan*/  X_Frames; } ;
struct TYPE_24__ {int /*<<< orphan*/  R_Errors; int /*<<< orphan*/  R_Bytes; int /*<<< orphan*/  R_Frames; int /*<<< orphan*/  X_Errors; int /*<<< orphan*/  X_Bytes; int /*<<< orphan*/  X_Frames; } ;
struct TYPE_23__ {int /*<<< orphan*/  R_Errors; int /*<<< orphan*/  R_Bytes; int /*<<< orphan*/  R_Frames; int /*<<< orphan*/  X_Errors; int /*<<< orphan*/  X_Bytes; int /*<<< orphan*/  X_Frames; } ;
struct TYPE_22__ {int /*<<< orphan*/  R_Errors; int /*<<< orphan*/  R_Bytes; int /*<<< orphan*/  R_Frames; int /*<<< orphan*/  X_Errors; int /*<<< orphan*/  X_Bytes; int /*<<< orphan*/  X_Frames; } ;
struct TYPE_21__ {int /*<<< orphan*/  Disc_Unspecified; int /*<<< orphan*/  Disc_App_Timeout; int /*<<< orphan*/  Disc_Page_Coding; int /*<<< orphan*/  Disc_Invalid_Msg; int /*<<< orphan*/  Disc_SUB_SEP_PWD; int /*<<< orphan*/  Disc_Supervisor; int /*<<< orphan*/  Disc_Long_Msg; int /*<<< orphan*/  Disc_No_Command; int /*<<< orphan*/  Disc_Incompat; int /*<<< orphan*/  Disc_Application; int /*<<< orphan*/  Disc_Unexpected; int /*<<< orphan*/  Disc_Training; int /*<<< orphan*/  Disc_No_Polling; int /*<<< orphan*/  Disc_Unexp_Msg; int /*<<< orphan*/  Disc_Retries; int /*<<< orphan*/  Disc_No_Response; int /*<<< orphan*/  Disc_Not_Ident; int /*<<< orphan*/  Disc_Normal; } ;
struct TYPE_20__ {int /*<<< orphan*/  Disc_V42bis; int /*<<< orphan*/  Disc_Frame_Rej; int /*<<< orphan*/  Disc_Incompat; int /*<<< orphan*/  Disc_Trn_Timeout; int /*<<< orphan*/  Disc_Carr_Wait; int /*<<< orphan*/  Disc_Congestion; int /*<<< orphan*/  Disc_Busy_Tone; int /*<<< orphan*/  Disc_Unspecified; int /*<<< orphan*/  Disc_Normal; } ;
struct TYPE_19__ {int /*<<< orphan*/  Ignored; int /*<<< orphan*/  Out_of_Order; int /*<<< orphan*/  Incompatible_Dst; int /*<<< orphan*/  Wrong_Number; int /*<<< orphan*/  Call_Rejected; int /*<<< orphan*/  User_Busy; int /*<<< orphan*/  Connected; int /*<<< orphan*/  Calls; } ;
struct TYPE_18__ {int /*<<< orphan*/  Other_Failures; int /*<<< orphan*/  Call_Rejected; int /*<<< orphan*/  Wrong_Number; int /*<<< orphan*/  No_Answer; int /*<<< orphan*/  User_Busy; int /*<<< orphan*/  Connected; int /*<<< orphan*/  Calls; } ;
struct TYPE_16__ {TYPE_9__ d2; TYPE_7__ d1; TYPE_6__ b2; TYPE_5__ b1; TYPE_4__ fax; TYPE_3__ mdm; TYPE_2__ inc; TYPE_1__ outg; } ;
struct TYPE_17__ {int Channels; size_t statistic_parse_first; size_t cur_parse_entry; size_t mdm_statistic_parse_first; int mdm_statistic_parse_last; int fax_statistic_parse_first; int fax_statistic_parse_last; int statistic_parse_last; TYPE_10__ InterfaceStat; TYPE_8__* parse_table; } ;
typedef  TYPE_11__ diva_strace_context_t ;
struct TYPE_25__ {int /*<<< orphan*/ * variable; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  diva_create_fax_parse_table (TYPE_11__*,int) ; 
 int /*<<< orphan*/  diva_create_line_parse_table (TYPE_11__*,int) ; 
 int /*<<< orphan*/  diva_create_modem_parse_table (TYPE_11__*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void diva_create_parse_table(diva_strace_context_t *pLib) {
	int i;

	for (i = 0; i < pLib->Channels; i++) {
		diva_create_line_parse_table(pLib, i);
		diva_create_modem_parse_table(pLib, i);
		diva_create_fax_parse_table(pLib, i);
	}

	pLib->statistic_parse_first = pLib->cur_parse_entry;

	/*
	  Outgoing Calls
	*/
	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Outgoing Calls\\Calls");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.outg.Calls;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Outgoing Calls\\Connected");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.outg.Connected;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Outgoing Calls\\User Busy");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.outg.User_Busy;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Outgoing Calls\\No Answer");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.outg.No_Answer;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Outgoing Calls\\Wrong Number");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.outg.Wrong_Number;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Outgoing Calls\\Call Rejected");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.outg.Call_Rejected;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Outgoing Calls\\Other Failures");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.outg.Other_Failures;

	/*
	  Incoming Calls
	*/
	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Incoming Calls\\Calls");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.inc.Calls;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Incoming Calls\\Connected");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.inc.Connected;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Incoming Calls\\User Busy");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.inc.User_Busy;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Incoming Calls\\Call Rejected");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.inc.Call_Rejected;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Incoming Calls\\Wrong Number");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.inc.Wrong_Number;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Incoming Calls\\Incompatible Dst");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.inc.Incompatible_Dst;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Incoming Calls\\Out of Order");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.inc.Out_of_Order;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Incoming Calls\\Ignored");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.inc.Ignored;

	/*
	  Modem Statistics
	*/
	pLib->mdm_statistic_parse_first = pLib->cur_parse_entry;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Modem\\Disc Normal");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.mdm.Disc_Normal;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Modem\\Disc Unspecified");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.mdm.Disc_Unspecified;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Modem\\Disc Busy Tone");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.mdm.Disc_Busy_Tone;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Modem\\Disc Congestion");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.mdm.Disc_Congestion;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Modem\\Disc Carr. Wait");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.mdm.Disc_Carr_Wait;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Modem\\Disc Trn Timeout");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.mdm.Disc_Trn_Timeout;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Modem\\Disc Incompat.");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.mdm.Disc_Incompat;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Modem\\Disc Frame Rej.");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.mdm.Disc_Frame_Rej;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\Modem\\Disc V42bis");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.mdm.Disc_V42bis;

	pLib->mdm_statistic_parse_last  = pLib->cur_parse_entry - 1;

	/*
	  Fax Statistics
	*/
	pLib->fax_statistic_parse_first = pLib->cur_parse_entry;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc Normal");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_Normal;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc Not Ident.");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_Not_Ident;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc No Response");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_No_Response;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc Retries");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_Retries;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc Unexp. Msg.");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_Unexp_Msg;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc No Polling.");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_No_Polling;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc Training");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_Training;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc Unexpected");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_Unexpected;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc Application");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_Application;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc Incompat.");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_Incompat;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc No Command");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_No_Command;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc Long Msg");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_Long_Msg;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc Supervisor");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_Supervisor;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc SUB SEP PWD");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_SUB_SEP_PWD;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc Invalid Msg");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_Invalid_Msg;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc Page Coding");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_Page_Coding;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc App Timeout");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_App_Timeout;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\FAX\\Disc Unspecified");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.fax.Disc_Unspecified;

	pLib->fax_statistic_parse_last  = pLib->cur_parse_entry - 1;

	/*
	  B-Layer1"
	*/
	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\B-Layer1\\X-Frames");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.b1.X_Frames;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\B-Layer1\\X-Bytes");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.b1.X_Bytes;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\B-Layer1\\X-Errors");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.b1.X_Errors;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\B-Layer1\\R-Frames");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.b1.R_Frames;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\B-Layer1\\R-Bytes");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.b1.R_Bytes;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\B-Layer1\\R-Errors");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.b1.R_Errors;

	/*
	  B-Layer2
	*/
	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\B-Layer2\\X-Frames");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.b2.X_Frames;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\B-Layer2\\X-Bytes");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.b2.X_Bytes;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\B-Layer2\\X-Errors");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.b2.X_Errors;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\B-Layer2\\R-Frames");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.b2.R_Frames;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\B-Layer2\\R-Bytes");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.b2.R_Bytes;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\B-Layer2\\R-Errors");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.b2.R_Errors;

	/*
	  D-Layer1
	*/
	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\D-Layer1\\X-Frames");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.d1.X_Frames;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\D-Layer1\\X-Bytes");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.d1.X_Bytes;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\D-Layer1\\X-Errors");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.d1.X_Errors;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\D-Layer1\\R-Frames");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.d1.R_Frames;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\D-Layer1\\R-Bytes");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.d1.R_Bytes;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\D-Layer1\\R-Errors");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.d1.R_Errors;

	/*
	  D-Layer2
	*/
	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\D-Layer2\\X-Frames");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.d2.X_Frames;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\D-Layer2\\X-Bytes");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.d2.X_Bytes;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\D-Layer2\\X-Errors");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.d2.X_Errors;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\D-Layer2\\R-Frames");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.d2.R_Frames;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\D-Layer2\\R-Bytes");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.d2.R_Bytes;

	strcpy(pLib->parse_table[pLib->cur_parse_entry].path,
	       "Statistics\\D-Layer2\\R-Errors");
	pLib->parse_table[pLib->cur_parse_entry++].variable = \
		&pLib->InterfaceStat.d2.R_Errors;


	pLib->statistic_parse_last  = pLib->cur_parse_entry - 1;
}