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
struct brcmf_if {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_fws_rxreorder (struct brcmf_if*,struct sk_buff*) ; 

__attribute__((used)) static void brcmf_proto_bcdc_rxreorder(struct brcmf_if *ifp,
				       struct sk_buff *skb)
{
	brcmf_fws_rxreorder(ifp, skb);
}