#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_5__ {TYPE_1__ sin_addr; } ;
union vxlan_addr {TYPE_3__ sa; TYPE_2__ sin; } ;
struct nlattr {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  nla_get_in_addr (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 

__attribute__((used)) static int vxlan_nla_get_addr(union vxlan_addr *ip, struct nlattr *nla)
{
	if (nla_len(nla) >= sizeof(struct in6_addr)) {
		return -EAFNOSUPPORT;
	} else if (nla_len(nla) >= sizeof(__be32)) {
		ip->sin.sin_addr.s_addr = nla_get_in_addr(nla);
		ip->sa.sa_family = AF_INET;
		return 0;
	} else {
		return -EAFNOSUPPORT;
	}
}