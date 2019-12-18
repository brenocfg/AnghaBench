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
struct msm_gem_address_space {int dummy; } ;
struct drm_framebuffer {scalar_t__* pitches; } ;
struct dpu_hw_fmt_layout {unsigned int num_planes; scalar_t__* plane_pitch; int /*<<< orphan*/ * plane_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  msm_framebuffer_iova (struct drm_framebuffer*,struct msm_gem_address_space*,unsigned int) ; 

__attribute__((used)) static int _dpu_format_populate_addrs_linear(
		struct msm_gem_address_space *aspace,
		struct drm_framebuffer *fb,
		struct dpu_hw_fmt_layout *layout)
{
	unsigned int i;

	/* Can now check the pitches given vs pitches expected */
	for (i = 0; i < layout->num_planes; ++i) {
		if (layout->plane_pitch[i] > fb->pitches[i]) {
			DRM_ERROR("plane %u expected pitch %u, fb %u\n",
				i, layout->plane_pitch[i], fb->pitches[i]);
			return -EINVAL;
		}
	}

	/* Populate addresses for simple formats here */
	for (i = 0; i < layout->num_planes; ++i) {
		if (aspace)
			layout->plane_addr[i] =
				msm_framebuffer_iova(fb, aspace, i);
		if (!layout->plane_addr[i]) {
			DRM_ERROR("failed to retrieve base addr\n");
			return -EFAULT;
		}
	}

	return 0;
}