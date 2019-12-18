#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct sk_buff {int /*<<< orphan*/  cb; scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_2__ stats; } ;
struct i2400m_roq_data {unsigned int sn; int cs; } ;
struct i2400m_roq {int /*<<< orphan*/  ws; } ;
struct i2400m_pl_edata_hdr {int cs; int /*<<< orphan*/  reorder; } ;
struct TYPE_3__ {struct net_device* net_dev; } ;
struct i2400m {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  rx_roq_refcount; struct i2400m_roq* rx_roq; TYPE_1__ wimax_dev; } ;
struct device {int dummy; } ;
typedef  enum i2400m_cs { ____Placeholder_i2400m_cs } i2400m_cs ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int I2400M_RO_CIN ; 
 unsigned int I2400M_RO_CIN_SHIFT ; 
 unsigned int I2400M_RO_NEEDED ; 
 unsigned int I2400M_RO_SN ; 
 unsigned int I2400M_RO_SN_SHIFT ; 
 unsigned int I2400M_RO_TYPE ; 
#define  I2400M_RO_TYPE_PACKET 131 
#define  I2400M_RO_TYPE_PACKET_WS 130 
#define  I2400M_RO_TYPE_RESET 129 
 unsigned int I2400M_RO_TYPE_SHIFT ; 
#define  I2400M_RO_TYPE_WS 128 
 int /*<<< orphan*/  __i2400m_roq_nsn (struct i2400m_roq*,unsigned int) ; 
 int /*<<< orphan*/  d_dump (int,struct device*,void const*,size_t) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*,struct sk_buff*,unsigned int,void const*,size_t) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*,struct sk_buff*,unsigned int,void const*,size_t) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int /*<<< orphan*/  i2400m_net_erx (struct i2400m*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  i2400m_roq_queue (struct i2400m*,struct i2400m_roq*,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  i2400m_roq_queue_update_ws (struct i2400m*,struct i2400m_roq*,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  i2400m_roq_reset (struct i2400m*,struct i2400m_roq*) ; 
 int /*<<< orphan*/  i2400m_roq_update_ws (struct i2400m*,struct i2400m_roq*,unsigned int) ; 
 int /*<<< orphan*/  i2400m_rx_roq_destroy ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_end_pointer (struct sk_buff*) ; 
 struct sk_buff* skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static
void i2400m_rx_edata(struct i2400m *i2400m, struct sk_buff *skb_rx,
		     unsigned single_last, const void *payload, size_t size)
{
	struct device *dev = i2400m_dev(i2400m);
	const struct i2400m_pl_edata_hdr *hdr = payload;
	struct net_device *net_dev = i2400m->wimax_dev.net_dev;
	struct sk_buff *skb;
	enum i2400m_cs cs;
	u32 reorder;
	unsigned ro_needed, ro_type, ro_cin, ro_sn;
	struct i2400m_roq *roq;
	struct i2400m_roq_data *roq_data;
	unsigned long flags;

	BUILD_BUG_ON(ETH_HLEN > sizeof(*hdr));

	d_fnstart(2, dev, "(i2400m %p skb_rx %p single %u payload %p "
		  "size %zu)\n", i2400m, skb_rx, single_last, payload, size);
	if (size < sizeof(*hdr)) {
		dev_err(dev, "ERX: HW BUG? message with short header (%zu "
			"vs %zu bytes expected)\n", size, sizeof(*hdr));
		goto error;
	}

	if (single_last) {
		skb = skb_get(skb_rx);
		d_printf(3, dev, "ERX: skb %p reusing\n", skb);
	} else {
		skb = skb_clone(skb_rx, GFP_KERNEL);
		if (skb == NULL) {
			dev_err(dev, "ERX: no memory to clone skb\n");
			net_dev->stats.rx_dropped++;
			goto error_skb_clone;
		}
		d_printf(3, dev, "ERX: skb %p cloned from %p\n", skb, skb_rx);
	}
	/* now we have to pull and trim so that the skb points to the
	 * beginning of the IP packet; the netdev part will add the
	 * ethernet header as needed - we know there is enough space
	 * because we checked in i2400m_rx_edata(). */
	skb_pull(skb, payload + sizeof(*hdr) - (void *) skb->data);
	skb_trim(skb, (void *) skb_end_pointer(skb) - payload - sizeof(*hdr));

	reorder = le32_to_cpu(hdr->reorder);
	ro_needed = reorder & I2400M_RO_NEEDED;
	cs = hdr->cs;
	if (ro_needed) {
		ro_type = (reorder >> I2400M_RO_TYPE_SHIFT) & I2400M_RO_TYPE;
		ro_cin = (reorder >> I2400M_RO_CIN_SHIFT) & I2400M_RO_CIN;
		ro_sn = (reorder >> I2400M_RO_SN_SHIFT) & I2400M_RO_SN;

		spin_lock_irqsave(&i2400m->rx_lock, flags);
		if (i2400m->rx_roq == NULL) {
			kfree_skb(skb);	/* rx_roq is already destroyed */
			spin_unlock_irqrestore(&i2400m->rx_lock, flags);
			goto error;
		}
		roq = &i2400m->rx_roq[ro_cin];
		kref_get(&i2400m->rx_roq_refcount);
		spin_unlock_irqrestore(&i2400m->rx_lock, flags);

		roq_data = (struct i2400m_roq_data *) &skb->cb;
		roq_data->sn = ro_sn;
		roq_data->cs = cs;
		d_printf(2, dev, "ERX: reorder needed: "
			 "type %u cin %u [ws %u] sn %u/%u len %zuB\n",
			 ro_type, ro_cin, roq->ws, ro_sn,
			 __i2400m_roq_nsn(roq, ro_sn), size);
		d_dump(2, dev, payload, size);
		switch(ro_type) {
		case I2400M_RO_TYPE_RESET:
			i2400m_roq_reset(i2400m, roq);
			kfree_skb(skb);	/* no data here */
			break;
		case I2400M_RO_TYPE_PACKET:
			i2400m_roq_queue(i2400m, roq, skb, ro_sn);
			break;
		case I2400M_RO_TYPE_WS:
			i2400m_roq_update_ws(i2400m, roq, ro_sn);
			kfree_skb(skb);	/* no data here */
			break;
		case I2400M_RO_TYPE_PACKET_WS:
			i2400m_roq_queue_update_ws(i2400m, roq, skb, ro_sn);
			break;
		default:
			dev_err(dev, "HW BUG? unknown reorder type %u\n", ro_type);
		}

		spin_lock_irqsave(&i2400m->rx_lock, flags);
		kref_put(&i2400m->rx_roq_refcount, i2400m_rx_roq_destroy);
		spin_unlock_irqrestore(&i2400m->rx_lock, flags);
	}
	else
		i2400m_net_erx(i2400m, skb, cs);
error_skb_clone:
error:
	d_fnend(2, dev, "(i2400m %p skb_rx %p single %u payload %p "
		"size %zu) = void\n", i2400m, skb_rx, single_last, payload, size);
}