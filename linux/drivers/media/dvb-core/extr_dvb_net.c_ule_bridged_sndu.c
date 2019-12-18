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
struct ethhdr {int /*<<< orphan*/  h_proto; } ;
struct dvb_net_priv {int ule_next_hdr; int ule_sndu_len; int ule_bridged; TYPE_1__* ule_skb; } ;
struct TYPE_2__ {int data; } ;

/* Variables and functions */
 int ETH_P_802_3_MIN ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ule_bridged_sndu( struct dvb_net_priv *p )
{
	struct ethhdr *hdr = (struct ethhdr*) p->ule_next_hdr;
	if(ntohs(hdr->h_proto) < ETH_P_802_3_MIN) {
		int framelen = p->ule_sndu_len - ((p->ule_next_hdr+sizeof(struct ethhdr)) - p->ule_skb->data);
		/* A frame Type < ETH_P_802_3_MIN for a bridged frame, introduces a LLC Length field. */
		if(framelen != ntohs(hdr->h_proto)) {
			return -1;
		}
	}
	/* Note:
	 * From RFC4326:
	 *  "A bridged SNDU is a Mandatory Extension Header of Type 1.
	 *   It must be the final (or only) extension header specified in the header chain of a SNDU."
	 * The 'ule_bridged' flag will cause the extension header processing loop to terminate.
	 */
	p->ule_bridged = 1;
	return 0;
}