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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {int frag; } ;
struct TYPE_4__ {int frag; } ;
struct ch_filter_specification {TYPE_1__ mask; TYPE_2__ val; } ;

/* Variables and functions */
 int EINVAL ; 
 int ntohl (int) ; 

__attribute__((used)) static inline int cxgb4_fill_ipv4_frag(struct ch_filter_specification *f,
				       u32 val, u32 mask)
{
	u32 mask_val;
	u8 frag_val;

	frag_val = (ntohl(val) >> 13) & 0x00000007;
	mask_val = ntohl(mask) & 0x0000FFFF;

	if (frag_val == 0x1 && mask_val != 0x3FFF) { /* MF set */
		f->val.frag = 1;
		f->mask.frag = 1;
	} else if (frag_val == 0x2 && mask_val != 0x3FFF) { /* DF set */
		f->val.frag = 0;
		f->mask.frag = 1;
	} else {
		return -EINVAL;
	}

	return 0;
}