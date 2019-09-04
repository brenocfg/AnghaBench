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
typedef  scalar_t__ uint32_t ;
struct msm_gem_address_space {int dummy; } ;
struct drm_framebuffer {scalar_t__* offsets; int /*<<< orphan*/ * obj; } ;

/* Variables and functions */
 scalar_t__ msm_gem_iova (int /*<<< orphan*/ ,struct msm_gem_address_space*) ; 

uint32_t msm_framebuffer_iova(struct drm_framebuffer *fb,
		struct msm_gem_address_space *aspace, int plane)
{
	if (!fb->obj[plane])
		return 0;
	return msm_gem_iova(fb->obj[plane], aspace) + fb->offsets[plane];
}