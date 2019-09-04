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
typedef  int /*<<< orphan*/  u32 ;
struct trace_seq {int dummy; } ;

/* Variables and functions */
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

const char *print_u32_array(
	struct trace_seq *p,
	u32 *arr, int len)
{
	int i;
	const char *ret = trace_seq_buffer_ptr(p);

	for (i = 0; i < len ; i++)
		trace_seq_printf(p, "%s%#x", i == 0 ? "" : " ", arr[i]);
	trace_seq_putc(p, 0);
	return ret;
}