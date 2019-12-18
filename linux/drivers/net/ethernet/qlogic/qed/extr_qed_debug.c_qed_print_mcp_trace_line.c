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
struct qed_hwfn {int dummy; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 int qed_parse_mcp_trace_buf (struct qed_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

enum dbg_status qed_print_mcp_trace_line(struct qed_hwfn *p_hwfn,
					 u8 *dump_buf,
					 u32 num_dumped_bytes,
					 char *results_buf)
{
	u32 parsed_results_bytes;

	return qed_parse_mcp_trace_buf(p_hwfn,
				       dump_buf,
				       num_dumped_bytes,
				       0,
				       num_dumped_bytes,
				       results_buf, &parsed_results_bytes);
}