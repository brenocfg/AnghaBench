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
typedef  int /*<<< orphan*/  u8 ;
struct iphdr {int ihl; int version; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; scalar_t__ check; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ttl; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  id; int /*<<< orphan*/  tot_len; int /*<<< orphan*/  tos; } ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ttl; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  id; int /*<<< orphan*/  tot_len; int /*<<< orphan*/  tos; } ;
struct ib_ud_header {TYPE_1__ ip4; } ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
 int /*<<< orphan*/  ip_fast_csum (int /*<<< orphan*/ *,int) ; 

__sum16 ib_ud_ip4_csum(struct ib_ud_header *header)
{
	struct iphdr iph;

	iph.ihl		= 5;
	iph.version	= 4;
	iph.tos		= header->ip4.tos;
	iph.tot_len	= header->ip4.tot_len;
	iph.id		= header->ip4.id;
	iph.frag_off	= header->ip4.frag_off;
	iph.ttl		= header->ip4.ttl;
	iph.protocol	= header->ip4.protocol;
	iph.check	= 0;
	iph.saddr	= header->ip4.saddr;
	iph.daddr	= header->ip4.daddr;

	return ip_fast_csum((u8 *)&iph, iph.ihl);
}