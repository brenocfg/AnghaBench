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
struct msm_gem_address_space {int dummy; } ;
struct drm_framebuffer {int /*<<< orphan*/ * obj; TYPE_1__* format; } ;
struct TYPE_2__ {int num_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_gem_unpin_iova (int /*<<< orphan*/ ,struct msm_gem_address_space*) ; 

void msm_framebuffer_cleanup(struct drm_framebuffer *fb,
		struct msm_gem_address_space *aspace)
{
	int i, n = fb->format->num_planes;

	for (i = 0; i < n; i++)
		msm_gem_unpin_iova(fb->obj[i], aspace);
}