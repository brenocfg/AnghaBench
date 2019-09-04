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
 int DELTA_FRAME_BSY ; 
 int DELTA_FRAME_DEC ; 
 int DELTA_FRAME_M2M ; 
 int DELTA_FRAME_OUT ; 
 int DELTA_FRAME_RDY ; 
 int DELTA_FRAME_REF ; 
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static inline char *frame_state_str(u32 state, char *str, unsigned int len)
{
	snprintf(str, len, "%s %s %s %s %s %s",
		 (state & DELTA_FRAME_REF)  ? "ref" : "   ",
		 (state & DELTA_FRAME_BSY)  ? "bsy" : "   ",
		 (state & DELTA_FRAME_DEC)  ? "dec" : "   ",
		 (state & DELTA_FRAME_OUT)  ? "out" : "   ",
		 (state & DELTA_FRAME_M2M)  ? "m2m" : "   ",
		 (state & DELTA_FRAME_RDY)  ? "rdy" : "   ");
	return str;
}