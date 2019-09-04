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
struct udphdr {int /*<<< orphan*/  dest; } ;
struct tcphdr {int /*<<< orphan*/  dest; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ arfs_get_ip_proto (struct sk_buff const*) ; 
 char* skb_transport_header (struct sk_buff const*) ; 

__attribute__((used)) static __be16 arfs_get_dst_port(const struct sk_buff *skb)
{
	char *transport_header;

	transport_header = skb_transport_header(skb);
	if (arfs_get_ip_proto(skb) == IPPROTO_TCP)
		return ((struct tcphdr *)transport_header)->dest;
	return ((struct udphdr *)transport_header)->dest;
}