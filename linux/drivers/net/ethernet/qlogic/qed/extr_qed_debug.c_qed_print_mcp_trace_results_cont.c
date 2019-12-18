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
struct qed_hwfn {int dummy; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 int qed_parse_mcp_trace_dump (struct qed_hwfn*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 

enum dbg_status qed_print_mcp_trace_results_cont(struct qed_hwfn *p_hwfn,
						 u32 *dump_buf,
						 char *results_buf)
{
	u32 parsed_buf_size;

	return qed_parse_mcp_trace_dump(p_hwfn, dump_buf, results_buf,
					&parsed_buf_size, false);
}