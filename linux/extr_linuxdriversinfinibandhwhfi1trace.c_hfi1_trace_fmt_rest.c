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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct trace_seq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTH_16B_PRN ; 
 int /*<<< orphan*/  BTH_9B_PRN ; 
 int /*<<< orphan*/  L4_FM_16B_PRN ; 
 scalar_t__ OPA_16B_L4_FM ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,int /*<<< orphan*/ ,scalar_t__,char const*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

const char *hfi1_trace_fmt_rest(struct trace_seq *p, bool bypass, u8 l4,
				u8 ack, bool becn, bool fecn, u8 mig,
				u8 se, u8 pad, u8 opcode, const char *opname,
				u8 tver, u16 pkey, u32 psn, u32 qpn,
				u32 dest_qpn, u32 src_qpn)
{
	const char *ret = trace_seq_buffer_ptr(p);

	if (bypass)
		if (l4 == OPA_16B_L4_FM)
			trace_seq_printf(p, L4_FM_16B_PRN,
					 opcode, opname, dest_qpn, src_qpn);
		else
			trace_seq_printf(p, BTH_16B_PRN,
					 opcode, opname,
					 se, mig, pad, tver, qpn, ack, psn);

	else
		trace_seq_printf(p, BTH_9B_PRN,
				 opcode, opname,
				 se, mig, pad, tver, pkey, fecn, becn,
				 qpn, ack, psn);
	trace_seq_putc(p, 0);

	return ret;
}