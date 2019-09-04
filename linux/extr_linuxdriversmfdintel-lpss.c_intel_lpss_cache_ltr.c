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
struct intel_lpss {scalar_t__ priv; void* idle_ltr; void* active_ltr; } ;

/* Variables and functions */
 scalar_t__ LPSS_PRIV_ACTIVELTR ; 
 scalar_t__ LPSS_PRIV_IDLELTR ; 
 void* readl (scalar_t__) ; 

__attribute__((used)) static void intel_lpss_cache_ltr(struct intel_lpss *lpss)
{
	lpss->active_ltr = readl(lpss->priv + LPSS_PRIV_ACTIVELTR);
	lpss->idle_ltr = readl(lpss->priv + LPSS_PRIV_IDLELTR);
}