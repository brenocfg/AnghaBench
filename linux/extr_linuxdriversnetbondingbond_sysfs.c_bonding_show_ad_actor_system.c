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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ad_actor_system; } ;
struct bonding {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ BOND_MODE (struct bonding*) ; 
 scalar_t__ BOND_MODE_8023AD ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct bonding* to_bond (struct device*) ; 

__attribute__((used)) static ssize_t bonding_show_ad_actor_system(struct device *d,
					    struct device_attribute *attr,
					    char *buf)
{
	struct bonding *bond = to_bond(d);

	if (BOND_MODE(bond) == BOND_MODE_8023AD && capable(CAP_NET_ADMIN))
		return sprintf(buf, "%pM\n", bond->params.ad_actor_system);

	return 0;
}