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
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int O2_DLL_LOCK_STATUS ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,struct sdhci_host*,int,int,int,int) ; 
 int /*<<< orphan*/  sdhci_o2_pll_dll_wdt_control ; 

__attribute__((used)) static int sdhci_o2_wait_dll_detect_lock(struct sdhci_host *host)
{
	u32	scratch32 = 0;

	return readx_poll_timeout(sdhci_o2_pll_dll_wdt_control, host,
		scratch32, !(scratch32 & O2_DLL_LOCK_STATUS), 1, 1000000);
}