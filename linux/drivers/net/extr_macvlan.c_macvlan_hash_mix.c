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
typedef  int /*<<< orphan*/  u32 ;
struct macvlan_dev {int dummy; } ;

/* Variables and functions */
 unsigned long L1_CACHE_SHIFT ; 

__attribute__((used)) static u32 macvlan_hash_mix(const struct macvlan_dev *vlan)
{
	return (u32)(((unsigned long)vlan) >> L1_CACHE_SHIFT);
}