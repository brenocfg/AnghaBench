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
struct intel_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wait_for_pipe_scanline_moving (struct intel_crtc*,int) ; 

__attribute__((used)) static void intel_wait_for_pipe_scanline_moving(struct intel_crtc *crtc)
{
	wait_for_pipe_scanline_moving(crtc, true);
}