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
struct sk_buff {int dummy; } ;
struct brcmf_pub {TYPE_1__* proto; } ;
struct brcmf_if {int dummy; } ;
struct TYPE_2__ {int (* hdrpull ) (struct brcmf_pub*,int,struct sk_buff*,struct brcmf_if**) ;} ;

/* Variables and functions */
 int stub1 (struct brcmf_pub*,int,struct sk_buff*,struct brcmf_if**) ; 

__attribute__((used)) static inline int brcmf_proto_hdrpull(struct brcmf_pub *drvr, bool do_fws,
				      struct sk_buff *skb,
				      struct brcmf_if **ifp)
{
	struct brcmf_if *tmp = NULL;

	/* assure protocol is always called with
	 * non-null initialized pointer.
	 */
	if (ifp)
		*ifp = NULL;
	else
		ifp = &tmp;
	return drvr->proto->hdrpull(drvr, do_fws, skb, ifp);
}