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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct trace_seq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *nvme_trace_admin_identify(struct trace_seq *p, u8 *cdw10)
{
	const char *ret = trace_seq_buffer_ptr(p);
	u8 cns = cdw10[0];
	u16 ctrlid = get_unaligned_le16(cdw10 + 2);

	trace_seq_printf(p, "cns=%u, ctrlid=%u", cns, ctrlid);
	trace_seq_putc(p, 0);

	return ret;
}