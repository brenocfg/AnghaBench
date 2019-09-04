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
struct drm_syncobj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_syncobj_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct drm_syncobj**) ; 
 int /*<<< orphan*/  ptr_mask_bits (struct drm_syncobj*,int) ; 

__attribute__((used)) static void
__free_fence_array(struct drm_syncobj **fences, unsigned int n)
{
	while (n--)
		drm_syncobj_put(ptr_mask_bits(fences[n], 2));
	kvfree(fences);
}