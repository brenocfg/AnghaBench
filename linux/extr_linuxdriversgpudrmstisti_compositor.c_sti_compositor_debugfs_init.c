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
struct sti_compositor {scalar_t__* mixer; scalar_t__* vid; } ;
struct drm_minor {int dummy; } ;

/* Variables and functions */
 unsigned int STI_MAX_MIXER ; 
 unsigned int STI_MAX_VID ; 
 int /*<<< orphan*/  sti_mixer_debugfs_init (scalar_t__,struct drm_minor*) ; 
 int /*<<< orphan*/  vid_debugfs_init (scalar_t__,struct drm_minor*) ; 

int sti_compositor_debugfs_init(struct sti_compositor *compo,
				struct drm_minor *minor)
{
	unsigned int i;

	for (i = 0; i < STI_MAX_VID; i++)
		if (compo->vid[i])
			vid_debugfs_init(compo->vid[i], minor);

	for (i = 0; i < STI_MAX_MIXER; i++)
		if (compo->mixer[i])
			sti_mixer_debugfs_init(compo->mixer[i], minor);

	return 0;
}