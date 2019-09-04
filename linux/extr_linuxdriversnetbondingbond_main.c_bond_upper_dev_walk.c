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
struct net_device {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ bond_confirm_addr (struct net_device*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bond_upper_dev_walk(struct net_device *upper, void *data)
{
	__be32 ip = *((__be32 *)data);

	return ip == bond_confirm_addr(upper, 0, ip);
}