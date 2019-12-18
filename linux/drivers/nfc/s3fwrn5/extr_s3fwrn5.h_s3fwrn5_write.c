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
struct sk_buff {int dummy; } ;
struct s3fwrn5_info {int /*<<< orphan*/  phy_id; TYPE_1__* phy_ops; } ;
struct TYPE_2__ {int (* write ) (int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static inline int s3fwrn5_write(struct s3fwrn5_info *info, struct sk_buff *skb)
{
	if (!info->phy_ops->write)
		return -ENOTSUPP;

	return info->phy_ops->write(info->phy_id, skb);
}