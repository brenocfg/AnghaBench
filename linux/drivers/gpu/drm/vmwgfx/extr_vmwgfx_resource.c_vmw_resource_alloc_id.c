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
struct vmw_resource {int id; TYPE_1__* func; struct vmw_private* dev_priv; } ;
struct vmw_private {int /*<<< orphan*/  resource_lock; struct idr* res_idr; } ;
struct idr {int dummy; } ;
struct TYPE_2__ {size_t res_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int idr_alloc (struct idr*,struct vmw_resource*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int vmw_resource_alloc_id(struct vmw_resource *res)
{
	struct vmw_private *dev_priv = res->dev_priv;
	int ret;
	struct idr *idr = &dev_priv->res_idr[res->func->res_type];

	BUG_ON(res->id != -1);

	idr_preload(GFP_KERNEL);
	spin_lock(&dev_priv->resource_lock);

	ret = idr_alloc(idr, res, 1, 0, GFP_NOWAIT);
	if (ret >= 0)
		res->id = ret;

	spin_unlock(&dev_priv->resource_lock);
	idr_preload_end();
	return ret < 0 ? ret : 0;
}