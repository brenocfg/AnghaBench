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
 int WDIOF_KEEPALIVEPING ; 
 scalar_t__ wb_smsc_wdt_get_timeout () ; 

__attribute__((used)) static int wb_smsc_wdt_status(void)
{
	return (wb_smsc_wdt_get_timeout() == 0) ? 0 : WDIOF_KEEPALIVEPING;
}