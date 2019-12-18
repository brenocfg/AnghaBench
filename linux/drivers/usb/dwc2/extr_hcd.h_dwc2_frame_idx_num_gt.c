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

/* Variables and functions */
 int FRLISTEN_64_SIZE ; 

__attribute__((used)) static inline bool dwc2_frame_idx_num_gt(u16 fr_idx1, u16 fr_idx2)
{
	u16 diff = fr_idx1 - fr_idx2;
	u16 sign = diff & (FRLISTEN_64_SIZE >> 1);

	return diff && !sign;
}