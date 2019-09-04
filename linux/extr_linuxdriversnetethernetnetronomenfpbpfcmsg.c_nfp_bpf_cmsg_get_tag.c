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
struct cmsg_hdr {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 unsigned int be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int nfp_bpf_cmsg_get_tag(struct sk_buff *skb)
{
	struct cmsg_hdr *hdr;

	hdr = (struct cmsg_hdr *)skb->data;

	return be16_to_cpu(hdr->tag);
}