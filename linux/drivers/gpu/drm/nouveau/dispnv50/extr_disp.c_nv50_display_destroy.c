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
struct nv50_disp {scalar_t__ sync; int /*<<< orphan*/  core; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nv50_disp*) ; 
 int /*<<< orphan*/  nouveau_bo_ref (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nouveau_bo_unmap (scalar_t__) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (scalar_t__) ; 
 TYPE_1__* nouveau_display (struct drm_device*) ; 
 int /*<<< orphan*/  nv50_core_del (int /*<<< orphan*/ *) ; 
 struct nv50_disp* nv50_disp (struct drm_device*) ; 

__attribute__((used)) static void
nv50_display_destroy(struct drm_device *dev)
{
	struct nv50_disp *disp = nv50_disp(dev);

	nv50_core_del(&disp->core);

	nouveau_bo_unmap(disp->sync);
	if (disp->sync)
		nouveau_bo_unpin(disp->sync);
	nouveau_bo_ref(NULL, &disp->sync);

	nouveau_display(dev)->priv = NULL;
	kfree(disp);
}