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
struct sti_plane {int dummy; } ;
struct sti_mixer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GAM_MIXER_CTL ; 
 int /*<<< orphan*/  sti_mixer_get_plane_mask (struct sti_plane*) ; 
 int /*<<< orphan*/  sti_mixer_reg_read (struct sti_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sti_mixer_reg_write (struct sti_mixer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sti_mixer_to_str (struct sti_mixer*) ; 
 int /*<<< orphan*/  sti_plane_to_str (struct sti_plane*) ; 

int sti_mixer_set_plane_status(struct sti_mixer *mixer,
			       struct sti_plane *plane, bool status)
{
	u32 mask, val;

	DRM_DEBUG_DRIVER("%s %s %s\n", status ? "enable" : "disable",
			 sti_mixer_to_str(mixer), sti_plane_to_str(plane));

	mask = sti_mixer_get_plane_mask(plane);
	if (!mask) {
		DRM_ERROR("Can't find layer mask\n");
		return -EINVAL;
	}

	val = sti_mixer_reg_read(mixer, GAM_MIXER_CTL);
	val &= ~mask;
	val |= status ? mask : 0;
	sti_mixer_reg_write(mixer, GAM_MIXER_CTL, val);

	return 0;
}