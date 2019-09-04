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

/* Variables and functions */
 int DTD_CHAN_SHFT ; 
 int DTD_DIR_SHFT ; 
 int DTD_MODE_SHFT ; 
 int DTD_PKT_TYPE ; 
 int DTD_PKT_TYPE_SHFT ; 
 int DTD_PRI_SHFT ; 

__attribute__((used)) static inline u32 dtd_pkt_ctl(bool mode, bool dir, int chan, int pri,
			int next_chan)
{
	return (DTD_PKT_TYPE << DTD_PKT_TYPE_SHFT) | (mode << DTD_MODE_SHFT) |
		(dir << DTD_DIR_SHFT) | (chan << DTD_CHAN_SHFT) |
		(pri << DTD_PRI_SHFT) | next_chan;
}