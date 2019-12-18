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
typedef  union phy_configure_opts {int dummy; } phy_configure_opts ;
struct phy {int /*<<< orphan*/  mutex; TYPE_1__* ops; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;
struct TYPE_2__ {int (* validate ) (struct phy*,int,int,union phy_configure_opts*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct phy*,int,int,union phy_configure_opts*) ; 

int phy_validate(struct phy *phy, enum phy_mode mode, int submode,
		 union phy_configure_opts *opts)
{
	int ret;

	if (!phy)
		return -EINVAL;

	if (!phy->ops->validate)
		return -EOPNOTSUPP;

	mutex_lock(&phy->mutex);
	ret = phy->ops->validate(phy, mode, submode, opts);
	mutex_unlock(&phy->mutex);

	return ret;
}