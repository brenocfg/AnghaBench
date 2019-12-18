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
struct vxlanhdr {int dummy; } ;
struct sk_buff {int remcsum_offload; } ;
struct gro_remcsum {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  csum_valid; } ;

/* Variables and functions */
 TYPE_1__* NAPI_GRO_CB (struct sk_buff*) ; 
 struct vxlanhdr* skb_gro_remcsum_process (struct sk_buff*,void*,unsigned int,size_t,size_t,size_t,struct gro_remcsum*,int) ; 
 size_t vxlan_rco_offset (int /*<<< orphan*/ ) ; 
 size_t vxlan_rco_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vxlanhdr *vxlan_gro_remcsum(struct sk_buff *skb,
					  unsigned int off,
					  struct vxlanhdr *vh, size_t hdrlen,
					  __be32 vni_field,
					  struct gro_remcsum *grc,
					  bool nopartial)
{
	size_t start, offset;

	if (skb->remcsum_offload)
		return vh;

	if (!NAPI_GRO_CB(skb)->csum_valid)
		return NULL;

	start = vxlan_rco_start(vni_field);
	offset = start + vxlan_rco_offset(vni_field);

	vh = skb_gro_remcsum_process(skb, (void *)vh, off, hdrlen,
				     start, offset, grc, nopartial);

	skb->remcsum_offload = 1;

	return vh;
}