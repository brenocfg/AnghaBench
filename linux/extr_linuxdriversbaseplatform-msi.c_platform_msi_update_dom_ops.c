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
struct msi_domain_ops {int /*<<< orphan*/ * set_desc; int /*<<< orphan*/ * msi_init; } ;
struct msi_domain_info {struct msi_domain_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/ * platform_msi_init ; 
 int /*<<< orphan*/ * platform_msi_set_desc ; 

__attribute__((used)) static void platform_msi_update_dom_ops(struct msi_domain_info *info)
{
	struct msi_domain_ops *ops = info->ops;

	BUG_ON(!ops);

	if (ops->msi_init == NULL)
		ops->msi_init = platform_msi_init;
	if (ops->set_desc == NULL)
		ops->set_desc = platform_msi_set_desc;
}