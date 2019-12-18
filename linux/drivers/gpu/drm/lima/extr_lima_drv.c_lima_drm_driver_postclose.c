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
struct lima_drm_priv {int /*<<< orphan*/  vm; int /*<<< orphan*/  ctx_mgr; } ;
struct drm_file {struct lima_drm_priv* driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct lima_drm_priv*) ; 
 int /*<<< orphan*/  lima_ctx_mgr_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lima_vm_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lima_drm_driver_postclose(struct drm_device *dev, struct drm_file *file)
{
	struct lima_drm_priv *priv = file->driver_priv;

	lima_ctx_mgr_fini(&priv->ctx_mgr);
	lima_vm_put(priv->vm);
	kfree(priv);
}