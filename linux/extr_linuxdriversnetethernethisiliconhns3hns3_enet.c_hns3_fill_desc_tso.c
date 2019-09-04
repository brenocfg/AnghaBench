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
struct hns3_enet_ring {int dummy; } ;
typedef  enum hns_desc_type { ____Placeholder_hns_desc_type } hns_desc_type ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int DESC_TYPE_PAGE ; 
 int DESC_TYPE_SKB ; 
 int HNS3_MAX_BD_SIZE ; 
 int hns3_fill_desc (struct hns3_enet_ring*,void*,int,scalar_t__,int,int) ; 

__attribute__((used)) static int hns3_fill_desc_tso(struct hns3_enet_ring *ring, void *priv,
			      int size, dma_addr_t dma, int frag_end,
			      enum hns_desc_type type)
{
	unsigned int frag_buf_num;
	unsigned int k;
	int sizeoflast;
	int ret;

	frag_buf_num = (size + HNS3_MAX_BD_SIZE - 1) / HNS3_MAX_BD_SIZE;
	sizeoflast = size % HNS3_MAX_BD_SIZE;
	sizeoflast = sizeoflast ? sizeoflast : HNS3_MAX_BD_SIZE;

	/* When the frag size is bigger than hardware, split this frag */
	for (k = 0; k < frag_buf_num; k++) {
		ret = hns3_fill_desc(ring, priv,
				     (k == frag_buf_num - 1) ?
				sizeoflast : HNS3_MAX_BD_SIZE,
				dma + HNS3_MAX_BD_SIZE * k,
				frag_end && (k == frag_buf_num - 1) ? 1 : 0,
				(type == DESC_TYPE_SKB && !k) ?
					DESC_TYPE_SKB : DESC_TYPE_PAGE);
		if (ret)
			return ret;
	}

	return 0;
}