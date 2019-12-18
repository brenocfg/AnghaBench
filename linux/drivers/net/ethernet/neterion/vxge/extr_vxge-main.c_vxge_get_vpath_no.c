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
typedef  int u32 ;
typedef  int u16 ;
struct vxgedev {int no_of_vpath; int* vpath_selector; } ;
struct tcphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sk_buff {scalar_t__ protocol; } ;
struct iphdr {int ihl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_is_fragment (struct iphdr*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 vxge_get_vpath_no(struct vxgedev *vdev, struct sk_buff *skb)
{
	u16 queue_len, counter = 0;
	if (skb->protocol == htons(ETH_P_IP)) {
		struct iphdr *ip;
		struct tcphdr *th;

		ip = ip_hdr(skb);

		if (!ip_is_fragment(ip)) {
			th = (struct tcphdr *)(((unsigned char *)ip) +
					ip->ihl*4);

			queue_len = vdev->no_of_vpath;
			counter = (ntohs(th->source) +
				ntohs(th->dest)) &
				vdev->vpath_selector[queue_len - 1];
			if (counter >= queue_len)
				counter = queue_len - 1;
		}
	}
	return counter;
}