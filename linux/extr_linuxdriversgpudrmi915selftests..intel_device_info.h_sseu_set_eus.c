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
typedef  int u16 ;
struct sseu_dev_info {int* eu_mask; int /*<<< orphan*/  max_eus_per_subslice; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int sseu_eu_idx (struct sseu_dev_info*,int,int) ; 

__attribute__((used)) static inline void sseu_set_eus(struct sseu_dev_info *sseu,
				int slice, int subslice, u16 eu_mask)
{
	int i, offset = sseu_eu_idx(sseu, slice, subslice);

	for (i = 0;
	     i < DIV_ROUND_UP(sseu->max_eus_per_subslice, BITS_PER_BYTE); i++) {
		sseu->eu_mask[offset + i] =
			(eu_mask >> (BITS_PER_BYTE * i)) & 0xff;
	}
}