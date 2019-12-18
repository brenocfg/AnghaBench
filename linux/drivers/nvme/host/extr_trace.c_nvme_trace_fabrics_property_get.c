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
typedef  int /*<<< orphan*/  u32 ;
struct trace_seq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *nvme_trace_fabrics_property_get(struct trace_seq *p, u8 *spc)
{
	const char *ret = trace_seq_buffer_ptr(p);
	u8 attrib = spc[0];
	u32 ofst = get_unaligned_le32(spc + 4);

	trace_seq_printf(p, "attrib=%u, ofst=0x%x", attrib, ofst);
	trace_seq_putc(p, 0);
	return ret;
}