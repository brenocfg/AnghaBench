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
typedef  char const* u8 ;
typedef  char const* u32 ;
typedef  char const* u16 ;
struct trace_seq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LRH_16B_PRN ; 
 int /*<<< orphan*/  LRH_9B_PRN ; 
 int /*<<< orphan*/  LRH_PRN ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

const char *hfi1_trace_fmt_lrh(struct trace_seq *p, bool bypass,
			       u8 age, bool becn, bool fecn, u8 l4,
			       u8 lnh, const char *lnh_name, u8 lver,
			       u8 rc, u8 sc, u8 sl, u16 entropy,
			       u16 len, u16 pkey, u32 dlid, u32 slid)
{
	const char *ret = trace_seq_buffer_ptr(p);

	trace_seq_printf(p, LRH_PRN, len, sc, dlid, slid);

	if (bypass)
		trace_seq_printf(p, LRH_16B_PRN,
				 age, becn, fecn, l4, rc, sc, pkey, entropy);

	else
		trace_seq_printf(p, LRH_9B_PRN,
				 lnh, lnh_name, lver, sl);
	trace_seq_putc(p, 0);

	return ret;
}