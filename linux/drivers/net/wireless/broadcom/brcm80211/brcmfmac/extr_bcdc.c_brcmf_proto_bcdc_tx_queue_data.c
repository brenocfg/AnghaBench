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
struct brcmf_bcdc {int /*<<< orphan*/  fws; } ;
struct TYPE_2__ {struct brcmf_bcdc* pd; } ;

/* Variables and functions */
 int brcmf_fws_process_skb (struct brcmf_if*,struct sk_buff*) ; 
 int /*<<< orphan*/  brcmf_fws_queue_skbs (int /*<<< orphan*/ ) ; 
 struct brcmf_if* brcmf_get_ifp (struct brcmf_pub*,int) ; 
 int brcmf_proto_txdata (struct brcmf_pub*,int,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int brcmf_proto_bcdc_tx_queue_data(struct brcmf_pub *drvr, int ifidx,
					  struct sk_buff *skb)
{
	struct brcmf_if *ifp = brcmf_get_ifp(drvr, ifidx);
	struct brcmf_bcdc *bcdc = drvr->proto->pd;

	if (!brcmf_fws_queue_skbs(bcdc->fws))
		return brcmf_proto_txdata(drvr, ifidx, 0, skb);

	return brcmf_fws_process_skb(ifp, skb);
}