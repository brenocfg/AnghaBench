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
struct intel_crtc_state {scalar_t__ gamma_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_GAMMA_ENABLE ; 

__attribute__((used)) static u32 i845_cursor_ctl_crtc(const struct intel_crtc_state *crtc_state)
{
	u32 cntl = 0;

	if (crtc_state->gamma_enable)
		cntl |= CURSOR_GAMMA_ENABLE;

	return cntl;
}