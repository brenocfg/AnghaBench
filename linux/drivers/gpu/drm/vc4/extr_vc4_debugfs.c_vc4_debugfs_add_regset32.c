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
struct drm_device {int dummy; } ;
struct debugfs_regset32 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vc4_debugfs_add_file (struct drm_device*,char const*,int /*<<< orphan*/ ,struct debugfs_regset32*) ; 
 int /*<<< orphan*/  vc4_debugfs_regset32 ; 

void vc4_debugfs_add_regset32(struct drm_device *drm,
			      const char *name,
			      struct debugfs_regset32 *regset)
{
	vc4_debugfs_add_file(drm, name, vc4_debugfs_regset32, regset);
}