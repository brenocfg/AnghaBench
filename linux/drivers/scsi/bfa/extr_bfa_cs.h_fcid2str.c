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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 

__attribute__((used)) static inline void
fcid2str(char *fcid_str, u32 fcid)
{
	union {
		u32 fcid;
		u8 byte[4];
	} f;

	f.fcid = fcid;
	sprintf(fcid_str, "%02x:%02x:%02x", f.byte[1], f.byte[2], f.byte[3]);
}