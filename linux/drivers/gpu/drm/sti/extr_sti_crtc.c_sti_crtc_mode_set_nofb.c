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
struct drm_crtc {TYPE_1__* state; } ;
struct TYPE_2__ {int /*<<< orphan*/  adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  sti_crtc_mode_set (struct drm_crtc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sti_crtc_mode_set_nofb(struct drm_crtc *crtc)
{
	sti_crtc_mode_set(crtc, &crtc->state->adjusted_mode);
}