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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct rtllib_info_element {int dummy; } ;
struct rtllib_authentication {int /*<<< orphan*/  status; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MFIE_TYPE_CHALLENGE ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 

__attribute__((used)) static inline u16 auth_parse(struct net_device *dev, struct sk_buff *skb,
			     u8 **challenge, int *chlen)
{
	struct rtllib_authentication *a;
	u8 *t;

	if (skb->len <  (sizeof(struct rtllib_authentication) -
	    sizeof(struct rtllib_info_element))) {
		netdev_dbg(dev, "invalid len in auth resp: %d\n", skb->len);
		return 0xcafe;
	}
	*challenge = NULL;
	a = (struct rtllib_authentication *) skb->data;
	if (skb->len > (sizeof(struct rtllib_authentication) + 3)) {
		t = skb->data + sizeof(struct rtllib_authentication);

		if (*(t++) == MFIE_TYPE_CHALLENGE) {
			*chlen = *(t++);
			*challenge = kmemdup(t, *chlen, GFP_ATOMIC);
			if (!*challenge)
				return -ENOMEM;
		}
	}
	return le16_to_cpu(a->status);
}