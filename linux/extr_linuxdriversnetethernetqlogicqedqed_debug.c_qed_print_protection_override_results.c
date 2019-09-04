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
 int qed_parse_protection_override_dump (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

enum dbg_status qed_print_protection_override_results(struct qed_hwfn *p_hwfn,
						      u32 *dump_buf,
						      u32 num_dumped_dwords,
						      char *results_buf)
{
	u32 parsed_buf_size;

	return qed_parse_protection_override_dump(dump_buf,
						  results_buf,
						  &parsed_buf_size);
}