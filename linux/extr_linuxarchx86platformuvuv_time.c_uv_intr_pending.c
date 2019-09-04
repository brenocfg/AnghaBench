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

/* Variables and functions */
 int UV1H_EVENT_OCCURRED0_RTC1_MASK ; 
 int /*<<< orphan*/  UVH_EVENT_OCCURRED0 ; 
 int /*<<< orphan*/  UVXH_EVENT_OCCURRED2 ; 
 int UVXH_EVENT_OCCURRED2_RTC_1_MASK ; 
 scalar_t__ is_uv1_hub () ; 
 scalar_t__ is_uvx_hub () ; 
 int uv_read_global_mmr64 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uv_intr_pending(int pnode)
{
	if (is_uv1_hub())
		return uv_read_global_mmr64(pnode, UVH_EVENT_OCCURRED0) &
			UV1H_EVENT_OCCURRED0_RTC1_MASK;
	else if (is_uvx_hub())
		return uv_read_global_mmr64(pnode, UVXH_EVENT_OCCURRED2) &
			UVXH_EVENT_OCCURRED2_RTC_1_MASK;
	return 0;
}