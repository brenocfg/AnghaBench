#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct solos_card {TYPE_2__* dev; } ;
struct sk_buff {int dummy; } ;
struct pkt_hdr {void* type; void* vci; void* vpi; void* size; } ;
struct TYPE_4__ {int /*<<< orphan*/  aal; } ;
struct atm_vcc {int /*<<< orphan*/  flags; TYPE_3__* dev; int /*<<< orphan*/  vci; int /*<<< orphan*/  vpi; TYPE_1__ qos; } ;
struct TYPE_6__ {struct solos_card* dev_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_AAL5 ; 
 int /*<<< orphan*/  ATM_VF_ADDR ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PKT_POPEN ; 
 int /*<<< orphan*/  SOLOS_CHAN (TYPE_3__*) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fpga_queue (struct solos_card*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pkt_hdr* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int popen(struct atm_vcc *vcc)
{
	struct solos_card *card = vcc->dev->dev_data;
	struct sk_buff *skb;
	struct pkt_hdr *header;

	if (vcc->qos.aal != ATM_AAL5) {
		dev_warn(&card->dev->dev, "Unsupported ATM type %d\n",
			 vcc->qos.aal);
		return -EINVAL;
	}

	skb = alloc_skb(sizeof(*header), GFP_KERNEL);
	if (!skb) {
		if (net_ratelimit())
			dev_warn(&card->dev->dev, "Failed to allocate sk_buff in popen()\n");
		return -ENOMEM;
	}
	header = skb_put(skb, sizeof(*header));

	header->size = cpu_to_le16(0);
	header->vpi = cpu_to_le16(vcc->vpi);
	header->vci = cpu_to_le16(vcc->vci);
	header->type = cpu_to_le16(PKT_POPEN);

	fpga_queue(card, SOLOS_CHAN(vcc->dev), skb, NULL);

	set_bit(ATM_VF_ADDR, &vcc->flags);
	set_bit(ATM_VF_READY, &vcc->flags);

	return 0;
}