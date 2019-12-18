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
typedef  int u32 ;

/* Variables and functions */
 int CR_DYN_SHIFT ; 
 scalar_t__ scnprintf (char*,int,char*,int,int,char const*,char*) ; 

__attribute__((used)) static void check_dyn_flag(u64 scratch0, char *p, int size, int *used,
			   int this_hfi, int hfi, u32 flag, const char *what)
{
	u32 mask;

	mask = flag << (hfi ? CR_DYN_SHIFT : 0);
	if (scratch0 & mask) {
		*used += scnprintf(p + *used, size - *used,
				   "  0x%08x - HFI%d %s in use, %s device\n",
				   mask, hfi, what,
				   this_hfi == hfi ? "this" : "other");
	}
}