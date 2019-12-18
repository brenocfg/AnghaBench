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

/* Variables and functions */
 int CTRL_BITPOS_A ; 
 int CTRL_BITPOS_DESCLIMIT ; 
 int CTRL_BITPOS_FIFOINDEXMASK ; 
 int CTRL_BITPOS_G ; 
 int CTRL_BITPOS_L2SZ ; 

__attribute__((used)) static inline int ctrl_set(int l2sz, int idxmask, int desclim)
{
	int active = 0, go = 1;
	return l2sz << CTRL_BITPOS_L2SZ |
	       idxmask << CTRL_BITPOS_FIFOINDEXMASK |
	       desclim << CTRL_BITPOS_DESCLIMIT |
	       active << CTRL_BITPOS_A |
	       go << CTRL_BITPOS_G;
}