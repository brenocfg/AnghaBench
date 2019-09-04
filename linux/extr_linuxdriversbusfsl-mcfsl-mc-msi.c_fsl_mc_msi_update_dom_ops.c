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
struct msi_domain_ops {scalar_t__ set_desc; } ;
struct msi_domain_info {struct msi_domain_ops* ops; } ;

/* Variables and functions */
 scalar_t__ fsl_mc_msi_set_desc ; 

__attribute__((used)) static void fsl_mc_msi_update_dom_ops(struct msi_domain_info *info)
{
	struct msi_domain_ops *ops = info->ops;

	if (!ops)
		return;

	/*
	 * set_desc should not be set by the caller
	 */
	if (!ops->set_desc)
		ops->set_desc = fsl_mc_msi_set_desc;
}