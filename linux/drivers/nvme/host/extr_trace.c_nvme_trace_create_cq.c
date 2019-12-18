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
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *nvme_trace_create_cq(struct trace_seq *p, u8 *cdw10)
{
	const char *ret = trace_seq_buffer_ptr(p);
	u16 cqid = get_unaligned_le16(cdw10);
	u16 qsize = get_unaligned_le16(cdw10 + 2);
	u16 cq_flags = get_unaligned_le16(cdw10 + 4);
	u16 irq_vector = get_unaligned_le16(cdw10 + 6);

	trace_seq_printf(p, "cqid=%u, qsize=%u, cq_flags=0x%x, irq_vector=%u",
			 cqid, qsize, cq_flags, irq_vector);
	trace_seq_putc(p, 0);

	return ret;
}