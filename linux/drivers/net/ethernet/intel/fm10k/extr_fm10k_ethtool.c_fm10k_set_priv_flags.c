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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FM10K_PRV_FLAG_LEN ; 

__attribute__((used)) static int fm10k_set_priv_flags(struct net_device *netdev, u32 priv_flags)
{
	if (priv_flags >= BIT(FM10K_PRV_FLAG_LEN))
		return -EINVAL;

	return 0;
}