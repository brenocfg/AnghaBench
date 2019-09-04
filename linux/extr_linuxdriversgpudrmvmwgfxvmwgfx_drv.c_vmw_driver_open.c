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
struct vmw_private {int /*<<< orphan*/  tdev; } ;
struct vmw_fpriv {int /*<<< orphan*/ * tfile; } ;
struct drm_file {struct vmw_fpriv* driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct vmw_fpriv*) ; 
 struct vmw_fpriv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ttm_object_file_init (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 

__attribute__((used)) static int vmw_driver_open(struct drm_device *dev, struct drm_file *file_priv)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	struct vmw_fpriv *vmw_fp;
	int ret = -ENOMEM;

	vmw_fp = kzalloc(sizeof(*vmw_fp), GFP_KERNEL);
	if (unlikely(!vmw_fp))
		return ret;

	vmw_fp->tfile = ttm_object_file_init(dev_priv->tdev, 10);
	if (unlikely(vmw_fp->tfile == NULL))
		goto out_no_tfile;

	file_priv->driver_priv = vmw_fp;

	return 0;

out_no_tfile:
	kfree(vmw_fp);
	return ret;
}