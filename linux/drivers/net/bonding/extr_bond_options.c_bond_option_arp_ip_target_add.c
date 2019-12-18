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
struct bonding {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int _bond_option_arp_ip_target_add (struct bonding*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bond_option_arp_ip_target_add(struct bonding *bond, __be32 target)
{
	return _bond_option_arp_ip_target_add(bond, target);
}