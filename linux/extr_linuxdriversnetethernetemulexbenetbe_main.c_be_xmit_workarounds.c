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
struct sk_buff {int len; } ;
struct be_wrb_params {int dummy; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int BE_MAX_GSO_SIZE ; 
 scalar_t__ BEx_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct sk_buff* be_lancer_xmit_workarounds (struct be_adapter*,struct sk_buff*,struct be_wrb_params*) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int pskb_trim (struct sk_buff*,int) ; 
 scalar_t__ skb_put_padto (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *be_xmit_workarounds(struct be_adapter *adapter,
					   struct sk_buff *skb,
					   struct be_wrb_params *wrb_params)
{
	int err;

	/* Lancer, SH and BE3 in SRIOV mode have a bug wherein
	 * packets that are 32b or less may cause a transmit stall
	 * on that port. The workaround is to pad such packets
	 * (len <= 32 bytes) to a minimum length of 36b.
	 */
	if (skb->len <= 32) {
		if (skb_put_padto(skb, 36))
			return NULL;
	}

	if (BEx_chip(adapter) || lancer_chip(adapter)) {
		skb = be_lancer_xmit_workarounds(adapter, skb, wrb_params);
		if (!skb)
			return NULL;
	}

	/* The stack can send us skbs with length greater than
	 * what the HW can handle. Trim the extra bytes.
	 */
	WARN_ON_ONCE(skb->len > BE_MAX_GSO_SIZE);
	err = pskb_trim(skb, BE_MAX_GSO_SIZE);
	WARN_ON(err);

	return skb;
}