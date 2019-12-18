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
struct sti_mixer {scalar_t__ id; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 scalar_t__ STI_MIXER_MAIN ; 
 struct sti_mixer* to_sti_mixer (struct drm_crtc*) ; 

bool sti_crtc_is_main(struct drm_crtc *crtc)
{
	struct sti_mixer *mixer = to_sti_mixer(crtc);

	if (mixer->id == STI_MIXER_MAIN)
		return true;

	return false;
}