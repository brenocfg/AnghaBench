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
typedef  unsigned long long u64 ;
struct seq_file {int dummy; } ;
struct field_desc {char* member_0; int member_1; int member_2; } ;

/* Variables and functions */
 unsigned long long const BIT (int) ; 
 int TPLA_SIZE ; 
 int /*<<< orphan*/  field_desc_show (struct seq_file*,unsigned long long const,struct field_desc*) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 struct field_desc* tp_la0 ; 

__attribute__((used)) static int tp_la_show3(struct seq_file *seq, void *v, int idx)
{
	static struct field_desc tp_la1[] = {
		{ "CplCmdIn", 56, 8 },
		{ "CplCmdOut", 48, 8 },
		{ "ESynOut", 47, 1 },
		{ "EAckOut", 46, 1 },
		{ "EFinOut", 45, 1 },
		{ "ERstOut", 44, 1 },
		{ "SynIn", 43, 1 },
		{ "AckIn", 42, 1 },
		{ "FinIn", 41, 1 },
		{ "RstIn", 40, 1 },
		{ "DataIn", 39, 1 },
		{ "DataInVld", 38, 1 },
		{ "PadIn", 37, 1 },
		{ "RxBufEmpty", 36, 1 },
		{ "RxDdp", 35, 1 },
		{ "RxFbCongestion", 34, 1 },
		{ "TxFbCongestion", 33, 1 },
		{ "TxPktSumSrdy", 32, 1 },
		{ "RcfUlpType", 28, 4 },
		{ "Eread", 27, 1 },
		{ "Ebypass", 26, 1 },
		{ "Esave", 25, 1 },
		{ "Static0", 24, 1 },
		{ "Cread", 23, 1 },
		{ "Cbypass", 22, 1 },
		{ "Csave", 21, 1 },
		{ "CPktOut", 20, 1 },
		{ "RxPagePoolFull", 18, 2 },
		{ "RxLpbkPkt", 17, 1 },
		{ "TxLpbkPkt", 16, 1 },
		{ "RxVfValid", 15, 1 },
		{ "SynLearned", 14, 1 },
		{ "SetDelEntry", 13, 1 },
		{ "SetInvEntry", 12, 1 },
		{ "CpcmdDvld", 11, 1 },
		{ "CpcmdSave", 10, 1 },
		{ "RxPstructsFull", 8, 2 },
		{ "EpcmdDvld", 7, 1 },
		{ "EpcmdFlush", 6, 1 },
		{ "EpcmdTrimPrefix", 5, 1 },
		{ "EpcmdTrimPostfix", 4, 1 },
		{ "ERssIp4Pkt", 3, 1 },
		{ "ERssIp6Pkt", 2, 1 },
		{ "ERssTcpUdpPkt", 1, 1 },
		{ "ERssFceFipPkt", 0, 1 },
		{ NULL }
	};
	static struct field_desc tp_la2[] = {
		{ "CplCmdIn", 56, 8 },
		{ "MpsVfVld", 55, 1 },
		{ "MpsPf", 52, 3 },
		{ "MpsVf", 44, 8 },
		{ "SynIn", 43, 1 },
		{ "AckIn", 42, 1 },
		{ "FinIn", 41, 1 },
		{ "RstIn", 40, 1 },
		{ "DataIn", 39, 1 },
		{ "DataInVld", 38, 1 },
		{ "PadIn", 37, 1 },
		{ "RxBufEmpty", 36, 1 },
		{ "RxDdp", 35, 1 },
		{ "RxFbCongestion", 34, 1 },
		{ "TxFbCongestion", 33, 1 },
		{ "TxPktSumSrdy", 32, 1 },
		{ "RcfUlpType", 28, 4 },
		{ "Eread", 27, 1 },
		{ "Ebypass", 26, 1 },
		{ "Esave", 25, 1 },
		{ "Static0", 24, 1 },
		{ "Cread", 23, 1 },
		{ "Cbypass", 22, 1 },
		{ "Csave", 21, 1 },
		{ "CPktOut", 20, 1 },
		{ "RxPagePoolFull", 18, 2 },
		{ "RxLpbkPkt", 17, 1 },
		{ "TxLpbkPkt", 16, 1 },
		{ "RxVfValid", 15, 1 },
		{ "SynLearned", 14, 1 },
		{ "SetDelEntry", 13, 1 },
		{ "SetInvEntry", 12, 1 },
		{ "CpcmdDvld", 11, 1 },
		{ "CpcmdSave", 10, 1 },
		{ "RxPstructsFull", 8, 2 },
		{ "EpcmdDvld", 7, 1 },
		{ "EpcmdFlush", 6, 1 },
		{ "EpcmdTrimPrefix", 5, 1 },
		{ "EpcmdTrimPostfix", 4, 1 },
		{ "ERssIp4Pkt", 3, 1 },
		{ "ERssIp6Pkt", 2, 1 },
		{ "ERssTcpUdpPkt", 1, 1 },
		{ "ERssFceFipPkt", 0, 1 },
		{ NULL }
	};
	const u64 *p = v;

	if (idx)
		seq_putc(seq, '\n');
	field_desc_show(seq, p[0], tp_la0);
	if (idx < (TPLA_SIZE / 2 - 1) || p[1] != ~0ULL)
		field_desc_show(seq, p[1], (p[0] & BIT(17)) ? tp_la2 : tp_la1);
	return 0;
}