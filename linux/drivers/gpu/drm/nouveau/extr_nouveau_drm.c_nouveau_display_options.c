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

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  nouveau_config ; 
 int /*<<< orphan*/  nouveau_debug ; 
 int /*<<< orphan*/  nouveau_duallink ; 
 int /*<<< orphan*/  nouveau_hdmimhz ; 
 int /*<<< orphan*/  nouveau_ignorelid ; 
 int /*<<< orphan*/  nouveau_modeset ; 
 int /*<<< orphan*/  nouveau_noaccel ; 
 int /*<<< orphan*/  nouveau_nofbaccel ; 
 int /*<<< orphan*/  nouveau_runtime_pm ; 
 int /*<<< orphan*/  nouveau_tv_disable ; 
 int /*<<< orphan*/  nouveau_vram_pushbuf ; 

__attribute__((used)) static void nouveau_display_options(void)
{
	DRM_DEBUG_DRIVER("Loading Nouveau with parameters:\n");

	DRM_DEBUG_DRIVER("... tv_disable   : %d\n", nouveau_tv_disable);
	DRM_DEBUG_DRIVER("... ignorelid    : %d\n", nouveau_ignorelid);
	DRM_DEBUG_DRIVER("... duallink     : %d\n", nouveau_duallink);
	DRM_DEBUG_DRIVER("... nofbaccel    : %d\n", nouveau_nofbaccel);
	DRM_DEBUG_DRIVER("... config       : %s\n", nouveau_config);
	DRM_DEBUG_DRIVER("... debug        : %s\n", nouveau_debug);
	DRM_DEBUG_DRIVER("... noaccel      : %d\n", nouveau_noaccel);
	DRM_DEBUG_DRIVER("... modeset      : %d\n", nouveau_modeset);
	DRM_DEBUG_DRIVER("... runpm        : %d\n", nouveau_runtime_pm);
	DRM_DEBUG_DRIVER("... vram_pushbuf : %d\n", nouveau_vram_pushbuf);
	DRM_DEBUG_DRIVER("... hdmimhz      : %d\n", nouveau_hdmimhz);
}