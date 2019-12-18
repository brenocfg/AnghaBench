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
struct s3fwrn5_info {int /*<<< orphan*/  phy_id; TYPE_1__* phy_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_wake ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int s3fwrn5_set_wake(struct s3fwrn5_info *info, bool wake)
{
	if (!info->phy_ops->set_wake)
		return -ENOTSUPP;

	info->phy_ops->set_wake(info->phy_id, wake);

	return 0;
}