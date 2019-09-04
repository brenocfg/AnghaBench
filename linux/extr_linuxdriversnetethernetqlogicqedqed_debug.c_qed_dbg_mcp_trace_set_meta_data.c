#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  size_in_dwords; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 TYPE_1__ s_mcp_trace_meta_arr ; 

void qed_dbg_mcp_trace_set_meta_data(u32 *data, u32 size)
{
	s_mcp_trace_meta_arr.ptr = data;
	s_mcp_trace_meta_arr.size_in_dwords = size;
}