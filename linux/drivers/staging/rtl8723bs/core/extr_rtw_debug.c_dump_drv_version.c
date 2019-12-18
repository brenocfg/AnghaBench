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
 int /*<<< orphan*/  DBG_871X_SEL_NL (void*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRIVERVERSION ; 

void dump_drv_version(void *sel)
{
	DBG_871X_SEL_NL(sel, "%s %s\n", "rtl8723bs", DRIVERVERSION);
}