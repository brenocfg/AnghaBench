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
struct nouveau_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_fence_unref (struct nouveau_fence**) ; 
 int /*<<< orphan*/  nouveau_fence_wait (struct nouveau_fence*,int,int) ; 

__attribute__((used)) static void nouveau_dmem_fence_done(struct nouveau_fence **fence)
{
	if (fence) {
		nouveau_fence_wait(*fence, true, false);
		nouveau_fence_unref(fence);
	} else {
		/*
		 * FIXME wait for channel to be IDLE before calling finalizing
		 * the hmem object.
		 */
	}
}