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
struct vmw_sg_table {int dummy; } ;
struct vmw_private {int capabilities; } ;
struct vmw_piter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SVGA_CAP_GMR2 ; 
 scalar_t__ unlikely (int) ; 
 int vmw_gmr2_bind (struct vmw_private*,struct vmw_piter*,unsigned long,int) ; 
 int /*<<< orphan*/  vmw_piter_next (struct vmw_piter*) ; 
 int /*<<< orphan*/  vmw_piter_start (struct vmw_piter*,struct vmw_sg_table const*,int /*<<< orphan*/ ) ; 

int vmw_gmr_bind(struct vmw_private *dev_priv,
		 const struct vmw_sg_table *vsgt,
		 unsigned long num_pages,
		 int gmr_id)
{
	struct vmw_piter data_iter;

	vmw_piter_start(&data_iter, vsgt, 0);

	if (unlikely(!vmw_piter_next(&data_iter)))
		return 0;

	if (unlikely(!(dev_priv->capabilities & SVGA_CAP_GMR2)))
		return -EINVAL;

	return vmw_gmr2_bind(dev_priv, &data_iter, num_pages, gmr_id);
}