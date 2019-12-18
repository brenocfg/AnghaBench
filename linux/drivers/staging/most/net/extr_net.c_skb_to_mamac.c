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
typedef  int u8 ;
struct sk_buff {int* data; scalar_t__ len; } ;
struct mbo {int* virt_address; unsigned int buffer_length; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ETH_HLEN ; 
 int HB (unsigned int) ; 
 void* LB (unsigned int) ; 
 unsigned int MDP_HDR_LEN ; 
 int /*<<< orphan*/  PMHL ; 
 int /*<<< orphan*/  PMS_DEF_PRIO ; 
 int PMS_FIFONO_MDP ; 
 int PMS_FIFONO_SHIFT ; 
 int PMS_MSGTYPE_DATA ; 
 int PMS_TELID_UNSEGM_MAMAC ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,...) ; 

__attribute__((used)) static int skb_to_mamac(const struct sk_buff *skb, struct mbo *mbo)
{
	u8 *buff = mbo->virt_address;
	static const u8 broadcast[] = { 0x03, 0xFF };
	const u8 *dest_addr = skb->data + 4;
	const u8 *eth_type = skb->data + 12;
	unsigned int payload_len = skb->len - ETH_HLEN;
	unsigned int mdp_len = payload_len + MDP_HDR_LEN;

	if (mbo->buffer_length < mdp_len) {
		pr_err("drop: too small buffer! (%d for %d)\n",
		       mbo->buffer_length, mdp_len);
		return -EINVAL;
	}

	if (skb->len < ETH_HLEN) {
		pr_err("drop: too small packet! (%d)\n", skb->len);
		return -EINVAL;
	}

	if (dest_addr[0] == 0xFF && dest_addr[1] == 0xFF)
		dest_addr = broadcast;

	*buff++ = HB(mdp_len - 2);
	*buff++ = LB(mdp_len - 2);

	*buff++ = PMHL;
	*buff++ = (PMS_FIFONO_MDP << PMS_FIFONO_SHIFT) | PMS_MSGTYPE_DATA;
	*buff++ = PMS_DEF_PRIO;
	*buff++ = dest_addr[0];
	*buff++ = dest_addr[1];
	*buff++ = 0x00;

	*buff++ = HB(payload_len + 6);
	*buff++ = LB(payload_len + 6);

	/* end of FPH here */

	*buff++ = eth_type[0];
	*buff++ = eth_type[1];
	*buff++ = 0;
	*buff++ = 0;

	*buff++ = PMS_TELID_UNSEGM_MAMAC << 4 | HB(payload_len);
	*buff++ = LB(payload_len);

	memcpy(buff, skb->data + ETH_HLEN, payload_len);
	mbo->buffer_length = mdp_len;
	return 0;
}