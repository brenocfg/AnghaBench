#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long dbgMask; } ;

/* Variables and functions */
 unsigned long DL_EVL ; 
 unsigned long DL_FTL ; 
 unsigned long DL_LOG ; 
 TYPE_1__ myDriverDebugHandle ; 

void
DbgSetLevel(unsigned long dbgMask)
{
	myDriverDebugHandle.dbgMask = dbgMask | (DL_EVL | DL_FTL | DL_LOG);
}