#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union hinic_l3 {TYPE_2__* v6; TYPE_1__* v4; } ;
typedef  int /*<<< orphan*/  __sum16 ;
struct TYPE_4__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_3__ {int version; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  csum_ipv6_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_tcpudp_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __sum16 csum_magic(union hinic_l3 *ip, unsigned short proto)
{
	return (ip->v4->version == 4) ?
		csum_tcpudp_magic(ip->v4->saddr, ip->v4->daddr, 0, proto, 0) :
		csum_ipv6_magic(&ip->v6->saddr, &ip->v6->daddr, 0, proto, 0);
}