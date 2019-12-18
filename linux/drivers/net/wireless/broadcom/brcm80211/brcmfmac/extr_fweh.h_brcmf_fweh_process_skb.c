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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ protocol; int len; } ;
struct brcmf_pub {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  usr_subtype; int /*<<< orphan*/ * oui; int /*<<< orphan*/  subtype; } ;
struct brcmf_event {TYPE_1__ hdr; } ;

/* Variables and functions */
 scalar_t__ BCMILCP_BCM_SUBTYPE_EVENT ; 
 int /*<<< orphan*/  BRCM_OUI ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_LINK_CTL ; 
 int /*<<< orphan*/  brcmf_fweh_process_event (struct brcmf_pub*,struct brcmf_event*,int) ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 scalar_t__ get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static inline void brcmf_fweh_process_skb(struct brcmf_pub *drvr,
					  struct sk_buff *skb, u16 stype)
{
	struct brcmf_event *event_packet;
	u16 subtype, usr_stype;

	/* only process events when protocol matches */
	if (skb->protocol != cpu_to_be16(ETH_P_LINK_CTL))
		return;

	if ((skb->len + ETH_HLEN) < sizeof(*event_packet))
		return;

	event_packet = (struct brcmf_event *)skb_mac_header(skb);

	/* check subtype if needed */
	if (unlikely(stype)) {
		subtype = get_unaligned_be16(&event_packet->hdr.subtype);
		if (subtype != stype)
			return;
	}

	/* check for BRCM oui match */
	if (memcmp(BRCM_OUI, &event_packet->hdr.oui[0],
		   sizeof(event_packet->hdr.oui)))
		return;

	/* final match on usr_subtype */
	usr_stype = get_unaligned_be16(&event_packet->hdr.usr_subtype);
	if (usr_stype != BCMILCP_BCM_SUBTYPE_EVENT)
		return;

	brcmf_fweh_process_event(drvr, event_packet, skb->len + ETH_HLEN);
}