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
struct vmw_private {struct vmw_cmdbuf_man* cman; scalar_t__ has_mob; } ;
struct vmw_cmdbuf_man {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_cmdbuf_man_destroy (struct vmw_cmdbuf_man*) ; 
 int vmw_cmdbuf_set_pool_size (struct vmw_cmdbuf_man*,int,int) ; 
 int vmw_otables_setup (struct vmw_private*) ; 

__attribute__((used)) static int vmw_request_device_late(struct vmw_private *dev_priv)
{
	int ret;

	if (dev_priv->has_mob) {
		ret = vmw_otables_setup(dev_priv);
		if (unlikely(ret != 0)) {
			DRM_ERROR("Unable to initialize "
				  "guest Memory OBjects.\n");
			return ret;
		}
	}

	if (dev_priv->cman) {
		ret = vmw_cmdbuf_set_pool_size(dev_priv->cman,
					       256*4096, 2*4096);
		if (ret) {
			struct vmw_cmdbuf_man *man = dev_priv->cman;

			dev_priv->cman = NULL;
			vmw_cmdbuf_man_destroy(man);
		}
	}

	return 0;
}