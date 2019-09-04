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
typedef  int u64 ;
struct kvmppc_slb {int base_page_size; } ;

/* Variables and functions */
#define  MMU_PAGE_16M 129 
#define  MMU_PAGE_64K 128 

__attribute__((used)) static int decode_pagesize(struct kvmppc_slb *slbe, u64 r)
{
	switch (slbe->base_page_size) {
	case MMU_PAGE_64K:
		if ((r & 0xf000) == 0x1000)
			return MMU_PAGE_64K;
		break;
	case MMU_PAGE_16M:
		if ((r & 0xff000) == 0)
			return MMU_PAGE_16M;
		break;
	}
	return -1;
}