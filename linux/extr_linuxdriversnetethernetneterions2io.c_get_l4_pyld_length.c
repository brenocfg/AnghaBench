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
struct tcphdr {int doff; } ;
struct iphdr {int ihl; int /*<<< orphan*/  tot_len; } ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int get_l4_pyld_length(struct iphdr *ip, struct tcphdr *tcp)
{
	return ntohs(ip->tot_len) - (ip->ihl << 2) - (tcp->doff << 2);
}