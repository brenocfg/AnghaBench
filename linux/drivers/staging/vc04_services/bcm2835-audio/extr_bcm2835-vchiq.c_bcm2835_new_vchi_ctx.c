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
struct device {int dummy; } ;
struct bcm2835_vchi_ctx {int /*<<< orphan*/ * vchi_instance; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int vchi_connect (int /*<<< orphan*/ *) ; 
 int vchi_initialise (int /*<<< orphan*/ **) ; 

int bcm2835_new_vchi_ctx(struct device *dev, struct bcm2835_vchi_ctx *vchi_ctx)
{
	int ret;

	/* Initialize and create a VCHI connection */
	ret = vchi_initialise(&vchi_ctx->vchi_instance);
	if (ret) {
		dev_err(dev, "failed to initialise VCHI instance (ret=%d)\n",
			ret);
		return -EIO;
	}

	ret = vchi_connect(vchi_ctx->vchi_instance);
	if (ret) {
		dev_dbg(dev, "failed to connect VCHI instance (ret=%d)\n",
			ret);

		kfree(vchi_ctx->vchi_instance);
		vchi_ctx->vchi_instance = NULL;

		return -EIO;
	}

	return 0;
}