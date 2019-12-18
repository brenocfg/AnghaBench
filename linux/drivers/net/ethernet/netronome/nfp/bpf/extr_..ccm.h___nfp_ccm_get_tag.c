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
struct nfp_ccm_hdr {int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */

__attribute__((used)) static inline __be16 __nfp_ccm_get_tag(struct sk_buff *skb)
{
	struct nfp_ccm_hdr *hdr;

	hdr = (struct nfp_ccm_hdr *)skb->data;

	return hdr->tag;
}