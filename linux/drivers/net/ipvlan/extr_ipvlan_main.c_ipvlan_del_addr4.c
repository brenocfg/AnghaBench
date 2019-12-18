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
struct ipvl_dev {int dummy; } ;
struct in_addr {int dummy; } ;

/* Variables and functions */
 void ipvlan_del_addr (struct ipvl_dev*,struct in_addr*,int) ; 

__attribute__((used)) static void ipvlan_del_addr4(struct ipvl_dev *ipvlan, struct in_addr *ip4_addr)
{
	return ipvlan_del_addr(ipvlan, ip4_addr, false);
}