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
struct bond_net {int /*<<< orphan*/  net; int /*<<< orphan*/  class_attr_bonding_masters; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_class_remove_file_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bond_destroy_sysfs(struct bond_net *bn)
{
	netdev_class_remove_file_ns(&bn->class_attr_bonding_masters, bn->net);
}