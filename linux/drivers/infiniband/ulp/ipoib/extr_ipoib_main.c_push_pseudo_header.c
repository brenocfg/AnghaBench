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
struct sk_buff {int dummy; } ;
struct ipoib_pseudo_header {int /*<<< orphan*/  hwaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFINIBAND_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct ipoib_pseudo_header* skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static void push_pseudo_header(struct sk_buff *skb, const char *daddr)
{
	struct ipoib_pseudo_header *phdr;

	phdr = skb_push(skb, sizeof(*phdr));
	memcpy(phdr->hwaddr, daddr, INFINIBAND_ALEN);
}