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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct tcphdr {int /*<<< orphan*/  seq; } ;
struct iphdr {int /*<<< orphan*/  tot_len; } ;
struct TYPE_2__ {scalar_t__ va; } ;
struct i40iw_puda_buf {int maclen; int tcphlen; scalar_t__ ipv4; TYPE_1__ mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 

void i40iw_ieq_update_tcpip_info(struct i40iw_puda_buf *buf, u16 length, u32 seqnum)
{
	struct tcphdr *tcph;
	struct iphdr *iph;
	u16 iphlen;
	u16 packetsize;
	u8 *addr = (u8 *)buf->mem.va;

	iphlen = (buf->ipv4) ? 20 : 40;
	iph = (struct iphdr *)(addr + buf->maclen);
	tcph = (struct tcphdr *)(addr + buf->maclen + iphlen);
	packetsize = length + buf->tcphlen + iphlen;

	iph->tot_len = htons(packetsize);
	tcph->seq = htonl(seqnum);
}