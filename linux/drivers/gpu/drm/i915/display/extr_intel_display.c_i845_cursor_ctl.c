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
typedef  int u32 ;
struct intel_plane_state {TYPE_1__* color_plane; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stride; } ;

/* Variables and functions */
 int CURSOR_ENABLE ; 
 int CURSOR_FORMAT_ARGB ; 
 int CURSOR_STRIDE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 i845_cursor_ctl(const struct intel_crtc_state *crtc_state,
			   const struct intel_plane_state *plane_state)
{
	return CURSOR_ENABLE |
		CURSOR_FORMAT_ARGB |
		CURSOR_STRIDE(plane_state->color_plane[0].stride);
}