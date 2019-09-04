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
 int qed_parse_idle_chk_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum dbg_status qed_get_idle_chk_results_buf_size(struct qed_hwfn *p_hwfn,
						  u32 *dump_buf,
						  u32 num_dumped_dwords,
						  u32 *results_buf_size)
{
	u32 num_errors, num_warnings;

	return qed_parse_idle_chk_dump(dump_buf,
				       num_dumped_dwords,
				       NULL,
				       results_buf_size,
				       &num_errors, &num_warnings);
}