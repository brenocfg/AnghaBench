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
struct nouveau_drm {scalar_t__ fence; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dtor ) (struct nouveau_drm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_accel_ce_fini (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nouveau_accel_gr_fini (struct nouveau_drm*) ; 
 TYPE_1__* nouveau_fence (struct nouveau_drm*) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_drm*) ; 

__attribute__((used)) static void
nouveau_accel_fini(struct nouveau_drm *drm)
{
	nouveau_accel_ce_fini(drm);
	nouveau_accel_gr_fini(drm);
	if (drm->fence)
		nouveau_fence(drm)->dtor(drm);
}