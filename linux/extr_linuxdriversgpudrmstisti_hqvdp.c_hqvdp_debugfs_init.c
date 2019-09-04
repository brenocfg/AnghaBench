#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sti_hqvdp {int dummy; } ;
struct drm_minor {int /*<<< orphan*/  debugfs_root; } ;
struct TYPE_4__ {struct sti_hqvdp* data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int drm_debugfs_create_files (TYPE_1__*,unsigned int,int /*<<< orphan*/ ,struct drm_minor*) ; 
 TYPE_1__* hqvdp_debugfs_files ; 

__attribute__((used)) static int hqvdp_debugfs_init(struct sti_hqvdp *hqvdp, struct drm_minor *minor)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(hqvdp_debugfs_files); i++)
		hqvdp_debugfs_files[i].data = hqvdp;

	return drm_debugfs_create_files(hqvdp_debugfs_files,
					ARRAY_SIZE(hqvdp_debugfs_files),
					minor->debugfs_root, minor);
}