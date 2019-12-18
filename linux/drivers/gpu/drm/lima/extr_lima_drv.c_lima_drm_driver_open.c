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
struct lima_drm_priv {int /*<<< orphan*/  ctx_mgr; int /*<<< orphan*/  vm; } ;
struct lima_device {int dummy; } ;
struct drm_file {struct lima_drm_priv* driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct lima_drm_priv*) ; 
 struct lima_drm_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_ctx_mgr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lima_vm_create (struct lima_device*) ; 
 struct lima_device* to_lima_dev (struct drm_device*) ; 

__attribute__((used)) static int lima_drm_driver_open(struct drm_device *dev, struct drm_file *file)
{
	int err;
	struct lima_drm_priv *priv;
	struct lima_device *ldev = to_lima_dev(dev);

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->vm = lima_vm_create(ldev);
	if (!priv->vm) {
		err = -ENOMEM;
		goto err_out0;
	}

	lima_ctx_mgr_init(&priv->ctx_mgr);

	file->driver_priv = priv;
	return 0;

err_out0:
	kfree(priv);
	return err;
}