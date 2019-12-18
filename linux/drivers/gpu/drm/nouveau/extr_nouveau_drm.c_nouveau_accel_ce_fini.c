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
struct TYPE_2__ {int /*<<< orphan*/  copy; } ;
struct nouveau_drm {int /*<<< orphan*/  cechan; TYPE_1__ ttm; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_channel_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_channel_idle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvif_object_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_accel_ce_fini(struct nouveau_drm *drm)
{
	nouveau_channel_idle(drm->cechan);
	nvif_object_fini(&drm->ttm.copy);
	nouveau_channel_del(&drm->cechan);
}