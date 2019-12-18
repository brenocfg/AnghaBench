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
struct sk_buff {scalar_t__ data; } ;
struct nfp_flower_cmsg_hdr {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct nfp_flower_cmsg_hdr *
nfp_flower_cmsg_get_hdr(struct sk_buff *skb)
{
	return (struct nfp_flower_cmsg_hdr *)skb->data;
}