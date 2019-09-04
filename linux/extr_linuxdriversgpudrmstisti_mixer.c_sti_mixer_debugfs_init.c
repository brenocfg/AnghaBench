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
struct sti_mixer {int id; } ;
struct drm_minor {int /*<<< orphan*/  debugfs_root; } ;
struct drm_info_list {struct sti_mixer* data; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct drm_info_list*) ; 
 int EINVAL ; 
#define  STI_MIXER_AUX 129 
#define  STI_MIXER_MAIN 128 
 int drm_debugfs_create_files (struct drm_info_list*,int,int /*<<< orphan*/ ,struct drm_minor*) ; 
 struct drm_info_list* mixer0_debugfs_files ; 
 struct drm_info_list* mixer1_debugfs_files ; 

int sti_mixer_debugfs_init(struct sti_mixer *mixer, struct drm_minor *minor)
{
	unsigned int i;
	struct drm_info_list *mixer_debugfs_files;
	int nb_files;

	switch (mixer->id) {
	case STI_MIXER_MAIN:
		mixer_debugfs_files = mixer0_debugfs_files;
		nb_files = ARRAY_SIZE(mixer0_debugfs_files);
		break;
	case STI_MIXER_AUX:
		mixer_debugfs_files = mixer1_debugfs_files;
		nb_files = ARRAY_SIZE(mixer1_debugfs_files);
		break;
	default:
		return -EINVAL;
	}

	for (i = 0; i < nb_files; i++)
		mixer_debugfs_files[i].data = mixer;

	return drm_debugfs_create_files(mixer_debugfs_files,
					nb_files,
					minor->debugfs_root, minor);
}