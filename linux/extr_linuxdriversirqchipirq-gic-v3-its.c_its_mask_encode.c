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

/* Variables and functions */
 int GENMASK_ULL (int,int) ; 

__attribute__((used)) static void its_mask_encode(u64 *raw_cmd, u64 val, int h, int l)
{
	u64 mask = GENMASK_ULL(h, l);
	*raw_cmd &= ~mask;
	*raw_cmd |= (val << l) & mask;
}